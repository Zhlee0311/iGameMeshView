//
// Created by 李正豪 on 2023/12/18.
//

#ifndef IGAMEVIEW_LITE_FAIRING_H
#define IGAMEVIEW_LITE_FAIRING_H

#include"MeshKernel/Mesh.h"
#include"MeshKernel/Vertex.h"
#include<Eigen/Dense>
#include<vector>
#include<algorithm>
#include<map>

using namespace MeshKernel;
using namespace std;


class Fairing {
public :
    explicit Fairing(SurfaceMesh &mesh, double rate) {
        model = &mesh;
        lamda = rate;
    }

    void Execute() {
        map<iGameVertexHandle, iGameVertex> newVertices;//用于更新顶点
        auto vertices = model->allvertices();//网格中所有点的“handle-vertex”键值对
        //遍历网格的所有点v ==> (handle,vertex)
        for (auto &v: vertices) {
            if (!model->isOnBoundary(v.first)) {
                const auto v0h = v.first;//该点的Handle
                auto NEs = model->NeighborEh(v.first);//该点的所有邻边NE==>(handle)
                double area = 0;
                iGameVertex laplace;
                for (auto NE: NEs) {
                    const auto v1h = model->NeighborVhFromEdge(v0h, NE);
                    iGameFaceHandle f1(-1);
                    iGameFaceHandle f2(-1);
                    iGameVertexHandle v2h, v3h;
                    const auto NFs = model->NeighborFh(NE);
                    for (auto NF: NFs) {
                        if (!f1.is_valid()) {
                            f1 = NF;
                        } else {
                            f2 = NF;
                        }
                    }
                    area += model->getFaceArea(f1) + model->getFaceArea(f2);//计算一条邻边的两个邻面的面积和
                    for (int i = 0; i < 3; i++) {
                        if (model->faces(f1).vh(i) != v0h && model->faces(f1).vh(i) != v1h) {
                            v2h = model->faces(f1).vh(i);
                        }
                        if (model->faces(f2).vh(i) != v0h && model->faces(f2).vh(i) != v1h) {
                            v3h = model->faces(f2).vh(i);
                        }
                    }
                    const auto v0 = model->vertices(v0h);
                    const auto v1 = model->vertices(v1h);
                    const auto v2 = model->vertices(v2h);
                    const auto v3 = model->vertices(v3h);

                    const auto v10 = v0 - v1;
                    const auto v20 = v0 - v2;
                    const auto v21 = v1 - v2;
                    const auto v30 = v0 - v3;
                    const auto v31 = v1 - v3;

                    double cotA = (v21 * v20) / (v21 % v20).norm();
                    double cotB = (v31 * v30) / (v31 % v30).norm();
                    laplace = laplace + v10 * (cotA + cotB);
                }
                laplace = laplace / (2 * area);
                laplace = laplace * lamda;
                newVertices[v.first] = model->vertices(v.first) - laplace;
            } else {
                newVertices[v.first] = model->vertices(v.first);
            }
        }
        for (auto &item: newVertices) {
            model->vertices(item.first) = item.second;
        }
    }

private:
    SurfaceMesh *model;//网格
    double lamda;//迭代速率
};


#endif //IGAMEVIEW_LITE_FAIRING_H


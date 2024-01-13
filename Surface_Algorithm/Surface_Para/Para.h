//
// Created by 李正豪 on 2024/1/3.
//

#ifndef IGAMEVIEW_LITE_PARA_H
#define IGAMEVIEW_LITE_PARA_H

#include<vector>
#include<Eigen/SparseLU>
#include<Eigen/IterativeLinearSolvers>
#include<Eigen/SparseCore>
#include<map>
#include"MeshKernel/Mesh.h"
#include"MeshKernel/Vertex.h"

using namespace MeshKernel;
using namespace std;


class Para {
public:
    explicit Para(SurfaceMesh &mesh) {
        model = &mesh;
    }

    void execute() {
        boundary();
        process();
    }

private:
    double WeightCal(iGameVertexHandle a, iGameVertexHandle b) {
        auto ab = model->getEhFromTwoVh(a, b);//ab两点形成的边
        auto nf = model->NeighborFh(ab);//ab的邻面

        //声明四个待处理的对象：两个邻面、两个相对的点
        iGameFaceHandle f1(-1);
        iGameFaceHandle f2(-1);
        iGameVertexHandle c, d;


        //实例化ab的两个邻面
        for (auto &y: nf) {
            if (!f1.is_valid()) {
                f1 = y;
            } else if (!f2.is_valid()) {
                f2 = y;
            }
        }
        //找到与ab边相对的两个点便于计算cot权
        for (int i = 0; i < 3; i++) {
            if (model->faces(f1).vh(i) != a && model->faces(f1).vh(i) != b) {
                c = model->faces(f1).vh(i);
            }
            if (model->faces(f2).vh(i) != a && model->faces(f2).vh(i) != b) {
                d = model->faces(f2).vh(i);
            }
        }
        const auto A = model->vertices(a);
        const auto B = model->vertices(b);
        const auto C = model->vertices(c);
        const auto D = model->vertices(d);

        const auto CA = A - C;
        const auto CB = B - C;
        const auto DA = A - D;
        const auto DB = B - D;

        //点乘比叉乘的大小，得到cot权
        double cot1 = (CA * CB) / (CA % CB).norm();
        double cot2 = (DA * DB) / (DA % DB).norm();


        return (cot1 + cot2);

    }

    void boundary() {
        vector<iGameVertexHandle> fbound;
        iGameVertex center(0, 0, 0);
        auto allvertices = model->allvertices();
        //收集所有边界点
        for (const auto &v: allvertices) {
            if (model->isOnBoundary(v.first)) {
                fbound.push_back(v.first);
                center += v.second;
            }
        }
        //求center平均，并将center作为“坐标原点”
        center /= (double) fbound.size();
        for (const auto &v: fbound) {
            iGameVertex tmp = model->vertices(v) - center;
            tmp.setZ(0.0);
            tmp = tmp.normalize();
            if (abs(tmp.x()) > abs(tmp.y())) {
                if (tmp.x() > 0) {
                    tmp.y() /= tmp.x();
                    tmp.x() = 1.0;
                } else {
                    tmp.y() /= -tmp.x();
                    tmp.x() = -1;
                }
            } else {
                if (tmp.y() > 0) {
                    tmp.x() /= tmp.y();
                    tmp.y() = 1;
                } else {
                    tmp.x() /= -tmp.y();
                    tmp.y() = -1;
                }
            }
            model->vertices(v) = tmp;
        }//将曲面边界映射到固定边界上
    }

    void process() {
        //稀疏矩阵存储拓扑关系
        Eigen::SparseMatrix<double> A(model->VertexSize(), model->VertexSize());
        //定义求解器
        Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::AMDOrdering<int> > solver;
        //添加非零元素的三元组向量
        vector<Eigen::Triplet<double> > tv;
        //方程右边的向量
        Eigen::VectorXd b_x(model->VertexSize());
        Eigen::VectorXd b_y(model->VertexSize());
        Eigen::VectorXd b_z(model->VertexSize());
        //填充L矩阵
        auto vertices = model->allvertices();
        for (auto v: vertices) {
            //边界点固定不变，因此需要添加约束
            if (model->isOnBoundary(v.first)) {
                Eigen::Triplet<double> temp(v.first, v.first, 1.0);
                tv.push_back(temp);
                b_x[v.first] = v.second.x();
                b_y[v.first] = v.second.y();
                b_z[v.first] = v.second.z();
            }
            //非边界点需要计算其各邻点的cot权，并在约束条件下解线性方程
            else {
                auto adjVertices = model->NeighborVh(v.first);
                double weightSum = 0;
                for (auto u: adjVertices) {
                    double w = WeightCal(v.first, u);
                    weightSum += w;
                    Eigen::Triplet<double> temp(v.first, u, w);
                    tv.push_back(temp);
                }
                Eigen::Triplet<double> temp(v.first, v.first, -weightSum);
                tv.push_back(temp);
                b_x[v.first] = 0.0;
                b_y[v.first] = 0.0;
                b_z[v.first] = 0.0;
            }
        }
        //解方程
        A.setFromTriplets(tv.begin(), tv.end());
        solver.analyzePattern(A);
        solver.factorize(A);
        Eigen::VectorXd x = solver.solve(b_x);
        Eigen::VectorXd y = solver.solve(b_y);
        Eigen::VectorXd z = solver.solve(b_z);
        //更新顶点
        for (const auto &v: vertices) {
            if (model->isOnBoundary(v.first))continue;
            model->vertices(v.first) = iGameVertex(x[v.first], y[v.first], z[v.first]);
        }
    }

    SurfaceMesh *model;
};

#endif //IGAMEVIEW_LITE_PARA_H

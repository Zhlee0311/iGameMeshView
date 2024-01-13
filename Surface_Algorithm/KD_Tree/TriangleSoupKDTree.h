//
// Created by te1t0ch1phead on 2022/4/19.
//

#ifndef IGAMEVIEW_TRIANGLESOUPKDTREE_H
#define IGAMEVIEW_TRIANGLESOUPKDTREE_H

#include "MeshKernel/Mesh.h"
#include <vector>
struct kdtnode
{public:
    bool exist;
    int l,r,fa,cut_type;
    int size = 0;
    MeshKernel::iGameVertex BBOXMIN,BBOXMAX;
    double cnt_plane;
    std::vector<MeshKernel::iGameFaceHandle>face_list;
    kdtnode(){exist =false;l=r=-1;}
};
class TriangleSoupKDTree {
public:
    TriangleSoupKDTree()=default;
    const double alpha=0.75;
    const int dim=3;
    std::vector<kdtnode>kdt;
    MeshKernel::SurfaceMesh * mesh;
    std::vector<std::vector<VH>> faces;
    std::vector<std::vector<double>> vertices;
    std::vector<std::pair<int,int> >face_record;

    TriangleSoupKDTree(MeshKernel::SurfaceMesh *);
    std::vector<MeshKernel::iGameFaceHandle> query_cross_face(MeshKernel::iGameFaceHandle);
    int root;
//private:
    int build_sub_tree(MeshKernel::iGameVertex BBOXMIN,
                       MeshKernel::iGameVertex BBOXMAX,
                       std::vector<MeshKernel::iGameFaceHandle> face_list,
                       int fa,
                       int cut_type);
    std::vector<MeshKernel::iGameFaceHandle> queryByHandle(int id, MeshKernel::iGameFaceHandle fh);

    //std::vector<MeshKernel::iGameFaceHandle> TriangleSoupKDTree::queryAll(int id);
};



#endif //IGAMEVIEW_TRIANGLESOUPKDTREE_H

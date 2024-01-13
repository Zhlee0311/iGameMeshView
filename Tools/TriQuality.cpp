//
// Created by te1t0ch1phead on 2022/7/1.
//
#include "Tools/TriQuality.h"

// 面积
double TriQuality::Area(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh)
{
    MeshKernel::iGameFace face = mesh.faces(fh);
    return ((mesh.vertices(face.vh(1)) - mesh.vertices(face.vh(0))) %
    (mesh.vertices(face.vh(2)) - mesh.vertices(face.vh(0)))).norm()/2;
}

double TriQuality::GetInternalAnglesOfVertex(Vex v0, Vex v1, Vex v2) {

    double cosa = (v1 - v0).normalize() * (v2 - v0).normalize();
    double angle = acos(cosa) * 180.0 /  PI;

    return angle;
}

double TriQuality::MaxAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh)
{
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }

    std::vector<double> angles;
    angles.push_back(GetInternalAnglesOfVertex(v[0], v[1], v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[1], v[0], v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[2], v[1], v[0]));

    return *std::max_element(angles.begin(), angles.end());
}



double TriQuality::MinAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh)
{
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }

    std::vector<double> angles;
    angles.push_back(GetInternalAnglesOfVertex(v[0], v[1], v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[1], v[0], v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[2], v[1], v[0]));

    return *std::min_element(angles.begin(), angles.end());
}

// 雅可比, range : [0, MAX], acceptable range [0, MAX], unit cube : 1
double TriQuality::Jacobian(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh)
{
    //be caution about order

    MeshKernel::iGameVertex first, second;
    double jacobian;

    MeshKernel::iGameVertex edge[3];


    edge[0]=mesh.vertices(mesh.faces(fh).vh(1)) - mesh.vertices(mesh.faces(fh).vh(0));

    edge[1]=mesh.vertices(mesh.faces(fh).vh(2)) - mesh.vertices(mesh.faces(fh).vh(0));

    edge[2]=mesh.vertices(mesh.faces(fh).vh(2)) - mesh.vertices(mesh.faces(fh).vh(1));
    first = edge[1] - edge[0];
    second = edge[2] - edge[0];

    MeshKernel::iGameVertex cross = first % second;
    jacobian = cross.norm();

    double max_edge_length_product;
    max_edge_length_product = std::max(edge[0].norm() * edge[1].norm(),
                                       std::max(edge[1].norm() * edge[2].norm(), edge[0].norm() * edge[2].norm()));



    jacobian *= (2/sqrt(3));
    jacobian /= max_edge_length_product;

    return jacobian;
}

// 纵横比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
double TriQuality::AspectRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh)
{
    auto f = mesh.faces(fh);
    std::vector<double>v;

    v.push_back((mesh.vertices(f.vh(1)) -  mesh.vertices(f.vh(0))).norm());
    v.push_back((mesh.vertices(f.vh(2)) -  mesh.vertices(f.vh(1))).norm());
    v.push_back((mesh.vertices(f.vh(0)) -  mesh.vertices(f.vh(2))).norm());


    return (*std::max_element(v.begin(),v.end())) * (v[0] + v[1] +v[2]  ) / (4*sqrt(3) * Area(fh , mesh)  );
}


double TriQuality::EdgeRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    auto f = mesh.faces(fh);
    std::vector<double>v;
    v.push_back((mesh.vertices(f.vh(1)) -  mesh.vertices(f.vh(0))).norm());
    v.push_back((mesh.vertices(f.vh(2)) -  mesh.vertices(f.vh(1))).norm());
    v.push_back((mesh.vertices(f.vh(0)) -  mesh.vertices(f.vh(2))).norm());


    return *std::max_element(v.begin(),v.end()) / *std::min_element(v.begin(),v.end());

}



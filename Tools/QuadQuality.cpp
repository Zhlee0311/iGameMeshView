//
// Created by WHISKING on 2022/7/13.
//

#include "QuadQuality.h"

// 面积 range : [0, MAX], acceptable range [0, MAX], unit cube : 1
double QuadQuality::Area(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }
    double area = ((v[0]-v[1])%(v[2]-v[1])).norm()/2 + ((v[0]-v[3])%(v[2]-v[3])).norm()/2;
    return area;
}

double QuadQuality::GetInternalAnglesOfVertex(Vex v0, Vex v1, Vex v2) {

    double cosa = (v1 - v0).normalize() * (v2 - v0).normalize();
    double angle = acos(cosa) * 180.0 /  PI;
    return angle;
}

// 最大角, range : [0, π], acceptable range [π/2, π3/4], unit cube : π/3
double QuadQuality::MaxAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }

    std::vector<double> angles;
    angles.push_back(GetInternalAnglesOfVertex(v[1],v[0],  v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[2],v[1],  v[3]));
    angles.push_back(GetInternalAnglesOfVertex(v[3],v[2],  v[0]));
    angles.push_back(GetInternalAnglesOfVertex(v[0],v[3],  v[1]));

    return *std::max_element(angles.begin(), angles.end());
}

// 最小角, range : [0, π], acceptable range [π/4, π/2], unit cube : π/3
double QuadQuality::MinAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }

    std::vector<double> angles;
    angles.push_back(GetInternalAnglesOfVertex(v[1],v[0],  v[2]));
    angles.push_back(GetInternalAnglesOfVertex(v[2],v[1],  v[3]));
    angles.push_back(GetInternalAnglesOfVertex(v[3],v[2],  v[0]));
    angles.push_back(GetInternalAnglesOfVertex(v[0],v[3],  v[1]));

    return *std::min_element(angles.begin(), angles.end());
}

// 雅可比, range : [0, MAX], acceptable range [0, MAX], unit cube : 1
double QuadQuality::Jacobian(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }
    Vec x_1 = (v[1]-v[0])+(v[2]-v[3]);
    Vec x_2 = (v[2]-v[1])+(v[3]-v[0]);
    Vec n_c = (x_1%x_2).normalize();
    std::vector<double> alpha;
    alpha.emplace_back(n_c*((v[0]-v[3])%(v[1]-v[0])).normalize());
    alpha.emplace_back(n_c*((v[1]-v[0])%(v[2]-v[1])).normalize());
    alpha.emplace_back(n_c*((v[2]-v[1])%(v[3]-v[2])).normalize());
    alpha.emplace_back(n_c*((v[3]-v[2])%(v[0]-v[3])).normalize());

    return *std::min_element(alpha.begin(), alpha.end());
}

// 纵横比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
double QuadQuality::AspectRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    auto f = mesh.faces(fh);
    std::vector<double>v;

    v.push_back((mesh.vertices(f.vh(1)) -  mesh.vertices(f.vh(0))).norm());
    v.push_back((mesh.vertices(f.vh(2)) -  mesh.vertices(f.vh(1))).norm());
    v.push_back((mesh.vertices(f.vh(3)) -  mesh.vertices(f.vh(2))).norm());
    v.push_back((mesh.vertices(f.vh(0)) -  mesh.vertices(f.vh(3))).norm());

    return (*std::max_element(v.begin(),v.end())) * (v[0] + v[1] +v[2] +v[3] ) / (4* Area(fh , mesh)  );
}

// 长宽比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
double QuadQuality::EdgeRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    auto f = mesh.faces(fh);
    std::vector<double>v;
    v.push_back((mesh.vertices(f.vh(1)) -  mesh.vertices(f.vh(0))).norm());
    v.push_back((mesh.vertices(f.vh(2)) -  mesh.vertices(f.vh(1))).norm());
    v.push_back((mesh.vertices(f.vh(3)) -  mesh.vertices(f.vh(2))).norm());
    v.push_back((mesh.vertices(f.vh(0)) -  mesh.vertices(f.vh(3))).norm());

    return *std::max_element(v.begin(),v.end()) / *std::min_element(v.begin(),v.end());
}

// 翘曲 , range : [0, 1], acceptable range [0, 0.7], unit cube : 0
double QuadQuality::Warpage(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }
    Vex n0 = ((v[0]-v[3])%(v[1]-v[0])).normalize();
    Vex n1 = ((v[1]-v[0])%(v[2]-v[1])).normalize();
    Vex n2 = ((v[2]-v[1])%(v[3]-v[2])).normalize();
    Vex n3 = ((v[3]-v[2])%(v[0]-v[3])).normalize();

    double m1 = (n0*n2)*(n0*n2)*(n0*n2);
    double m2 = (n1*n3)*(n1*n3)*(n1*n3);

    return 1 - std::min(m1, m2);
}

// 锥度, range : [0, MAX], acceptable range [0, 0.7], unit cube : 0
double QuadQuality::Taper(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }
    Vec x_1 = (v[1]-v[0])+(v[2]-v[3]);
    Vec x_2 = (v[2]-v[1])+(v[3]-v[0]);
    Vec x_12 = (v[0]-v[1])+(v[2]-v[3]);

    return x_12.norm()/std::min(x_1.norm(),x_2.norm());
}

// 歪斜度 , range : [0, 1], acceptable range [0.5, 1], unit cube : 1
double QuadQuality::Skew(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh){
    MeshKernel::iGameFace face = mesh.faces(fh);
    std::vector<MeshKernel::iGameVertexHandle> vhs = face.getVertexHandle();
    std::vector<MeshKernel::iGameVertex> v;
    for (MeshKernel::iGameVertexHandle vh : vhs) {
        v.push_back(mesh.vertices(vh));
    }
    Vec x_1 = (v[1]-v[0])+(v[2]-v[3]);
    Vec x_2 = (v[2]-v[1])+(v[3]-v[0]);
    Vec x_1_norm = x_1/x_1.norm();
    Vec x_2_norm = x_2/x_2.norm();

    return std::abs(x_1_norm*x_2_norm);
}
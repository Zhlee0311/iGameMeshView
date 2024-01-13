//
// Created by te1t0ch1phead on 2022/7/1.
//

#ifndef IGAMEVIEW_TRIANGLEMESHQUALITY_H
#define IGAMEVIEW_TRIANGLEMESHQUALITY_H
#include <MeshKernel/Mesh.h>
#include <Eigen/Core>
#include <limits>
#include <algorithm>
#include <set>
#include <vector>
# define PI acos(-1)

class TriQuality
{


public:
    // 面积 range : [0, MAX], acceptable range [0, MAX]
    static double Area(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 最大角, range : [0, 180], acceptable range [60, 90], unit cube : 60
    static double MaxAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 最小角, range : [0, 180], acceptable range [30, 60], unit cube : 60
    static double MinAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 雅可比, range : [0, MAX], acceptable range [0, MAX], unit cube : 1
    static double Jacobian(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 纵横比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
    static double AspectRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 长宽比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
    static double EdgeRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    static double GetInternalAnglesOfVertex(Vex v0, Vex v1, Vex v2);
};
#endif //IGAMEVIEW_TRIANGLEMESHQUALITY_H

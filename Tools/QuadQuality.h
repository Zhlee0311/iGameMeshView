//
// Created by WHISKING on 2022/7/13.
//

#ifndef IGAMEVIEW_QUADQUALITY_H
#define IGAMEVIEW_QUADQUALITY_H
#include <MeshKernel/Mesh.h>
#include <Eigen/Core>
#include <limits>
#include <algorithm>
#include <set>
#include <vector>
# define PI acos(-1)

class QuadQuality {
public:
    // 面积 range : [0, MAX], acceptable range [0, MAX]
    static double Area(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 最大角, range : [0, π], acceptable range [π/2, π3/4], unit cube : π/2
    static double MaxAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 最小角, range : [0, π], acceptable range [π/4, π/2], unit cube : π/2
    static double MinAngle(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 雅可比, range : [0, MAX], acceptable range [0, MAX], unit cube : 1
    static double Jacobian(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 纵横比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
    static double AspectRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 长宽比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
    static double EdgeRatio(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 翘曲 , range : [0, 1], acceptable range [0, 0.7], unit cube : 0
    static double Warpage(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 锥度, range : [0, MAX], acceptable range [0, 0.7], unit cube : 0
    static double Taper(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    // 歪斜度 , range : [0, 1], acceptable range [0.5, 1], unit cube : 1
    static double Skew(MeshKernel::iGameFaceHandle fh, MeshKernel::SurfaceMesh& mesh);

    static double GetInternalAnglesOfVertex(Vex v0, Vex v1, Vex v2);
};


#endif //IGAMEVIEW_QUADQUALITY_H

#include <MeshKernel/Mesh.h>

template<typename T>
struct HexElementMetrics
{
    T Volume;
    T Taper;
    T Jacobian;
    T EdgeRatio;
    T MaximunEdgeRatio;
    T Skew;
    T Strech;
    T Diagnol;
    T RelativeSizeSquared;
};
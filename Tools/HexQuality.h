#include <MeshKernel/Mesh.h>
#include <Eigen/Core>
#include <limits>
#include <algorithm>

class HexQuality
{

private:
    static Eigen::Vector3f convertV2EV(MeshKernel::iGameVertex& v)
    {
        return Eigen::Vector3f(v.x(), v.y(), v.z());
    }
public:
    // 体积
    static float hex_volume(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        auto X_1 = (P_1 - P_0) + (P_2 - P_3) + (P_5 - P_4) + (P_6 - P_7);
        auto X_2 = (P_3 - P_0) + (P_2 - P_1) + (P_7 - P_4) + (P_6 - P_5);
        auto X_3 = (P_4 - P_0) + (P_5 - P_1) + (P_6 - P_2) + (P_7 - P_3);


        return X_1.dot(X_2.cross(X_3)) / 64.0;
    }

    // 锥度, range : [0, MAX], acceptable range [0, 0.5], unit cube : 0
    static float hex_taper(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        auto X_1 = (P_1 - P_0) + (P_2 - P_3) + (P_5 - P_4) + (P_6 - P_7);
        auto X_2 = (P_3 - P_0) + (P_2 - P_1) + (P_7 - P_4) + (P_6 - P_5);
        auto X_3 = (P_4 - P_0) + (P_5 - P_1) + (P_6 - P_2) + (P_7 - P_3);

        auto X_12 = (P_2 - P_3) - (P_1 - P_0) + (P_6 - P_7) - (P_5 - P_4);
        auto X_13 = (P_5 - P_1) - (P_4 - P_0) + (P_6 - P_2) - (P_7 - P_3);
        auto X_23 = (P_7 - P_4) - (P_3 - P_0) + (P_6 - P_5) - (P_2 - P_1);

        auto T_12 = X_12.norm() / ((std::min)(X_1.norm(), X_2.norm()));
        auto T_13 = X_13.norm() / ((std::min)(X_1.norm(), X_3.norm()));
        auto T_23 = X_23.norm() / ((std::min)(X_2.norm(), X_3.norm()));

        return (std::max)({T_12, T_13, T_23});
    }

    // 雅可比, range : [0, MAX], acceptable range [0, MAX], unit cube : 1
    static float hex_jacobian(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        //be caution about order

        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        float jacobian = (std::numeric_limits<float>::max)();
        float current_jacobian = 0.0;

        Eigen::Vector3f L_0, L_2, L_3;

        L_0 = P_1 - P_0;
        L_2 = P_3 - P_0;
        L_3 = P_4 - P_0;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_2 - P_1;
        L_2 = P_0 - P_1;
        L_3 = P_5 - P_1;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_3 - P_2;
        L_2 = P_1 - P_2;
        L_3 = P_6 - P_2;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_0 - P_3;
        L_2 = P_2 - P_3;
        L_3 = P_7 - P_3;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_7 - P_4;
        L_2 = P_5 - P_4;
        L_3 = P_0 - P_4;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_4 - P_5;
        L_2 = P_6 - P_5;
        L_3 = P_1 - P_5;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_5 - P_6;
        L_2 = P_7 - P_6;
        L_3 = P_2 - P_6;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        L_0 = P_6 - P_7;
        L_2 = P_4 - P_7;
        L_3 = P_3 - P_7;

        current_jacobian = (L_2.cross(L_3)).dot(L_0);
        if (current_jacobian < jacobian) jacobian = current_jacobian;

        return jacobian;
    }

    // 长宽比 , range : [1, MAX], acceptable range [1, MAX], unit cube : 1
    static float hex_edge_ratio(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        std::vector<float> lengths(12, 0);
        lengths[0] = (P_1 - P_0).norm();
        lengths[1] = (P_2 - P_1).norm();
        lengths[2] = (P_3 - P_2).norm();
        lengths[3] = (P_3 - P_0).norm();
        lengths[4] = (P_4 - P_0).norm();
        lengths[5] = (P_5 - P_1).norm();
        lengths[6] = (P_6 - P_2).norm();
        lengths[7] = (P_7 - P_3).norm();
        lengths[8] = (P_5 - P_4).norm();
        lengths[9] = (P_6 - P_5).norm();
        lengths[10] = (P_7 - P_6).norm();
        lengths[11] = (P_7 - P_4).norm();

        auto max_ele = std::max_element(lengths.begin(), lengths.end());
        auto min_ele = std::min_element(lengths.begin(), lengths.end());

        return *max_ele / *min_ele;
    }

    // 最大长宽比 , range : [1, MAX], acceptable range [1, 1.3], unit cube : 1
    static float hex_maximum_edge_ratio(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        auto X_1 = (P_1 - P_0) + (P_2 - P_3) + (P_5 - P_4) + (P_6 - P_7);
        auto X_2 = (P_3 - P_0) + (P_2 - P_1) + (P_7 - P_4) + (P_6 - P_5);
        auto X_3 = (P_4 - P_0) + (P_5 - P_1) + (P_6 - P_2) + (P_7 - P_3);

        auto L_1 = X_1.norm();
        auto L_2 = X_2.norm();
        auto L_3 = X_3.norm();

        auto A_12 = (std::max)(L_1 / L_2, L_2 / L_1);
        auto A_13 = (std::max)(L_1 / L_3, L_3 / L_1);
        auto A_23 = (std::max)(L_2 / L_3, L_3 / L_2);

        return (std::max)({A_12, A_13, A_23});
    }

    // 体积歪斜度/歪斜度 , range : [0, 1], acceptable range [0, 0.5], unit cube : 0
    static float hex_skew(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        auto X_1 = (P_1 - P_0) + (P_2 - P_3) + (P_5 - P_4) + (P_6 - P_7);
        auto X_2 = (P_3 - P_0) + (P_2 - P_1) + (P_7 - P_4) + (P_6 - P_5);
        auto X_3 = (P_4 - P_0) + (P_5 - P_1) + (P_6 - P_2) + (P_7 - P_3);

        auto X_1_hat = X_1.normalized();
        auto X_2_hat = X_2.normalized();
        auto X_3_hat = X_3.normalized();

        auto skew_12 = std::abs(X_1_hat.dot(X_2_hat));
        auto skew_13 = std::abs(X_1_hat.dot(X_3_hat));
        auto skew_23 = std::abs(X_2_hat.dot(X_3_hat));

        return (std::max)({skew_12, skew_13, skew_23});
    }

    // 伸展度 , range : [0, 1], acceptable range [0.25, 1], unit cube : 1
    static float hex_strech(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        std::vector<float> edges(12, 0);
        edges[0] = (P_1 - P_0).norm();
        edges[1] = (P_2 - P_1).norm();
        edges[2] = (P_3 - P_2).norm();
        edges[3] = (P_3 - P_0).norm();
        edges[4] = (P_4 - P_0).norm();
        edges[5] = (P_5 - P_1).norm();
        edges[6] = (P_6 - P_2).norm();
        edges[7] = (P_7 - P_3).norm();
        edges[8] = (P_5 - P_4).norm();
        edges[9] = (P_6 - P_5).norm();
        edges[10] = (P_7 - P_6).norm();
        edges[11] = (P_7 - P_4).norm();

        std::vector<float> diagonals(4, 0);

        diagonals[0] = (P_6 - P_0).norm();
        diagonals[1] = (P_7 - P_1).norm();
        diagonals[2] = (P_4 - P_2).norm();
        diagonals[3] = (P_5 - P_3).norm();

        float L_min = *(std::min_element(edges.begin(), edges.end()));
        float D_max = *(std::max_element(diagonals.begin(), diagonals.end()));

        return std::sqrt(3.0f) * L_min / D_max;
    }

    // 对角线长度比值, range : [0, 1], acceptable range [0.65, 1], unit cube : 1
    static float hex_diagonal(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh)
    {
        auto c = mesh.cells(ch);
        auto vhs = c.getVertexHandle();
        auto P_0 = convertV2EV(mesh.vertices(vhs[0]));
        auto P_1 = convertV2EV(mesh.vertices(vhs[1]));
        auto P_2 = convertV2EV(mesh.vertices(vhs[2]));
        auto P_3 = convertV2EV(mesh.vertices(vhs[3]));
        auto P_4 = convertV2EV(mesh.vertices(vhs[4]));
        auto P_5 = convertV2EV(mesh.vertices(vhs[5]));
        auto P_6 = convertV2EV(mesh.vertices(vhs[6]));
        auto P_7 = convertV2EV(mesh.vertices(vhs[7]));

        std::vector<float> diagonals(4, 0);

        diagonals[0] = (P_6 - P_0).norm();
        diagonals[1] = (P_7 - P_1).norm();
        diagonals[2] = (P_4 - P_2).norm();
        diagonals[3] = (P_5 - P_3).norm();

        auto max_ele = std::max_element(diagonals.begin(), diagonals.end());
        auto min_ele = std::min_element(diagonals.begin(), diagonals.end());

        return *min_ele / *max_ele ;

    }

    // 相对大小平方, range : [0, 1], acceptable range [0, 1], unit cube : 依赖于平均体积
    static float hex_relative_size_squared(MeshKernel::iGameCellHandle ch, MeshKernel::VolumeMesh& mesh, float average_volume)
    {
        auto D =  hex_volume(ch, mesh) / average_volume;
        auto sqr_q = (std::min)(D, 1.0f/D);

        return sqr_q * sqr_q;
    }

};
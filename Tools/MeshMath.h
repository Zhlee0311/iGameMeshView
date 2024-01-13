#pragma once
#include "MeshKernel/Mesh.h"
#ifndef IGMAE_KERNEL_SIMPLIFY
#define IGMAE_KERNEL_SIMPLIFY
typedef MeshKernel::iGameVertex Vex;
typedef MeshKernel::iGameVertex Vec;
typedef MeshKernel::iGameVertexHandle VH;
typedef MeshKernel::iGameEdgeHandle EH;
typedef MeshKernel::iGameFaceHandle FH;
typedef MeshKernel::iGameCellHandle CH;
#endif

/* 将会在此继续更新一些关于网格的数学函数 */

namespace MeshMath {

    // 表面网格的体积
	double get_volume_surface_mesh(MeshKernel::SurfaceMesh& mesh) {
		double volume_mesh = 0;
		for (auto& fp : mesh.allfaces()) {
			const auto& vhs = fp.second.getVertexHandle();
			for (int i = 2; i < vhs.size(); ++i) {
				auto& v0 = mesh.vertices(vhs[0]);
				auto& v1 = mesh.vertices(vhs[i - 1]);
				auto& v2 = mesh.vertices(vhs[i]);
				double v_tet = (v0 % v1) * (v2);
				volume_mesh += v_tet;
			}
		}
		return std::abs(volume_mesh) / 6.f;
	}

    // 四面体网格的体积
	double get_volume_tetahedral_mesh(MeshKernel::VolumeMesh& mesh) {
		double volume_mesh = 0;
		for (auto& fp : mesh.allfaces()) {
			if (!mesh.isOnBoundary(fp.first)) continue;
			const auto& vhs = fp.second.getVertexHandle();
			auto& v0 = mesh.vertices(vhs[0]);
			auto& v1 = mesh.vertices(vhs[1]);
			auto& v2 = mesh.vertices(vhs[2]);
			double v_tet = (v0 % v1) * (v2);
			volume_mesh += v_tet;
		}
		return std::abs(volume_mesh) / 6.f;
	}

    // 六面体网格的体积
	double get_volume_hexahedral_mesh(MeshKernel::VolumeMesh& mesh) {
		double volume_mesh = 0;

		for (auto& fp : mesh.allfaces()) {
			if (mesh.isOnBoundary(fp.first)) {
				const auto& vhs = fp.second.getVertexHandle();
				std::vector<std::vector<MeshKernel::iGameVertexHandle>> tri_vhs = {
					{ vhs[0], vhs[1], vhs[2] }, { vhs[2], vhs[3], vhs[0]}
				};
				for (auto& t_vhs : tri_vhs) {
					auto& v0 = mesh.vertices(vhs[0]);
					auto& v1 = mesh.vertices(vhs[1]);
					auto& v2 = mesh.vertices(vhs[2]);
					double v_tet = (v0 % v1) * (v2);
					volume_mesh += v_tet;
				}
			}
		}

		return std::abs(volume_mesh) / 6.f;
	}

	//void calc_cross_field(std::vector<Vec3>& points, std::vector<ID3>& triangles, std::vector<ID2>& feature_edges,
	//	std::vector<ID3>& singularities, std::vector<std::array<double, 9>>& global_triangle_dir) {

	//	// singularities: singularity id
	//	// singularities[0] != NO_ID, singluarity_v and its global id
	//	// singularities[1] != NO_ID, singularity_e and the edge is face_( f_id = singularities[1] / 3) 's edge_(fe_id = singularities[1] % 3, e form fv[fe_id] to fv[fe_id+1%3])
	//	// singularities[2] != NO_ID, singularity_f and its global id

	//	// global_triangle_dir: cross field dir
	//	// global_triangle_dir[i][0-2, 3-5, 6-8] = dir_vex(face[i][0, 1, 2])

	//	CrossField_Slover app;
	//	app.calc_cross_field(points, triangles, feature_edges,
	//		singularities, global_triangle_dir);// 计算标架场

	//}

    // 六面体中一个体素最小标量雅克比值
	double get_min_scaled_Jacobian_HexMesh(MeshKernel::VolumeMesh& mesh, CH ch) {// 返回该体素的最小标量雅克比值

		auto& c = mesh.cells(ch);
		double min_det = 2.f;// the value of Scaled Jacobian is the	determinant of the matrix Jacobian
		std::unordered_map<int, std::vector<int>> neighbor;
		const auto& _ehs = c.getEdgeHandle();
		for (auto& _eh : _ehs) {
			auto& _e = mesh.edges(_eh);
			auto& vh1 = _e.vh1();
			auto& vh2 = _e.vh2();
			neighbor[vh1].push_back(vh2);
			neighbor[vh2].push_back(vh1);
		}
		const auto& _vhs = c.getVertexHandle();
		for (auto& _vh : _vhs) {
			auto& v = mesh.vertices(_vh);
			auto adjvh = neighbor[_vh];
			assert(adjvh.size() == 3);
			auto v1 = mesh.vertices(VH(adjvh[0]));
			auto v2 = mesh.vertices(VH(adjvh[1]));
			auto v3 = mesh.vertices(VH(adjvh[2]));
			auto center = (v1 + v2 + v3) / 3;
			auto vec = (center - v).normalize();

			// ajust oridering
			auto vec12 = v2 - v1, vec13 = v3 - v1;
			auto normal = (vec12 % vec13).normalize();
			double cosine = vec * normal;
			if (cosine < 0) std::swap(v2, v3);

			std::vector<Eigen::Vector3d> ev(3);
			auto tmp = v1 - v;
			ev[0] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();
			tmp = v2 - v;
			ev[1] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();
			tmp = v3 - v;
			ev[2] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();

			Eigen::Matrix3d J;
			J << ev[0][0], ev[1][0], ev[2][0],
				ev[0][1], ev[1][1], ev[2][1],
				ev[0][2], ev[1][2], ev[2][2];
			//std::cout << J << endl;
			/*
			For an element, the full range of the Scaled Jacobian value is from −1 to + 1.
			And fscaled_jacobian = 1 if the element is an ideal element,
			fscaled_jacobian = −1 if the element is a worst distorted element
			*/
			min_det = std::min(min_det, J.determinant());
		}

		if (min_det < 0) std::cout << "Worning: There exist too bad hexahedron!!!\n";

		return min_det;

	}

    // 六面体中一个体素平均标量雅克比值
	double get_avg_scaled_Jacobian_HexMesh(MeshKernel::VolumeMesh& mesh, CH ch) {// 返回该体素的平均标量雅克比值

		auto& c = mesh.cells(ch);
		double sum_det = 0.f;// the value of Scaled Jacobian is the	determinant of the matrix Jacobian
		std::unordered_map<int, std::vector<int>> neighbor;
		const auto& _ehs = c.getEdgeHandle();
		for (auto& _eh : _ehs) {
			auto& _e = mesh.edges(_eh);
			auto& vh1 = _e.vh1();
			auto& vh2 = _e.vh2();
			neighbor[vh1].push_back(vh2);
			neighbor[vh2].push_back(vh1);
		}
		const auto& _vhs = c.getVertexHandle();
		for (auto& _vh : _vhs) {
			auto& v = mesh.vertices(_vh);
			auto adjvh = neighbor[_vh];
			assert(adjvh.size() == 3);
			auto v1 = mesh.vertices(VH(adjvh[0]));
			auto v2 = mesh.vertices(VH(adjvh[1]));
			auto v3 = mesh.vertices(VH(adjvh[2]));
			auto center = (v1 + v2 + v3) / 3;
			auto vec = (center - v).normalize();

			// ajust oridering
			auto vec12 = v2 - v1, vec13 = v3 - v1;
			auto normal = (vec12 % vec13).normalize();
			double cosine = vec * normal;
			if (cosine < 0) std::swap(v2, v3);

			std::vector<Eigen::Vector3d> ev(3);
			auto tmp = v1 - v;
			ev[0] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();
			tmp = v2 - v;
			ev[1] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();
			tmp = v3 - v;
			ev[2] = (Eigen::Vector3d(tmp.x(), tmp.y(), tmp.z())).normalized();

			Eigen::Matrix3d J;
			J << ev[0][0], ev[1][0], ev[2][0],
				ev[0][1], ev[1][1], ev[2][1],
				ev[0][2], ev[1][2], ev[2][2];
			//std::cout << J << endl;
			/*
			For an element, the full range of the Scaled Jacobian value is from −1 to + 1.
			And fscaled_jacobian = 1 if the element is an ideal element,
			fscaled_jacobian = −1 if the element is a worst distorted element
			*/
			sum_det += J.determinant();
		}

		return sum_det / _vhs.size();

	}

    // 表面网格中一个面最小角质量，返回0-1之间的值
	double get_min_angle_quality_SurfaceMesh(MeshKernel::SurfaceMesh& mesh, FH fh) {
		// 值越大 三角形/四边形 质量越好
		auto vhs = mesh.faces(fh).getVertexHandle();
		double min_angle = 180.f;
		int n = vhs.size();
		for (int i = 0; i < n; ++i) {
			auto& v0 = mesh.vertices(vhs[i]);
			auto& v1 = mesh.vertices(vhs[(i + 1) % n]);
			auto& v2 = mesh.vertices(vhs[(i + 2) % n]);
			auto vec10 = (v0 - v1).normalize();
			auto vec12 = (v2 - v1).normalize();
			double angle = std::acos(vec10 * vec12) / M_PI * 180;
			min_angle = std::min(min_angle, angle);
		}
		double val = std::fmin(1, n == 3 ? (min_angle / 60.0) : (min_angle) / 90.0);
		//std::cout << "val: " << val << std::endl;
		return val;

	}

    // 四面体中一个体素的AR质量，低纵横比（aspect ratio）意味着更好的形状
	double get_aspect_ratio_TetMesh(MeshKernel::VolumeMesh& mesh, CH ch) { // A value between √2/√3 and +∞. A low-aspect ratio implies a better shape.
		/*The aspect ratio, η(τ ), of a tetrahedron τ can be defined as the ratio between the longest edge length
		lmax and the shortest height hmin, that is, η(τ ) = lmax/hmin. It measures the “roundness”
		of a tetrahedron in terms of a value between √2/√3 and +∞. A low-aspect ratio implies a better shape.*/
		
		double best_ar = 0.8165;// √2/√3
		double len_max = 0.f;
		auto& cell = mesh.cells(ch);
		const auto& vhs = cell.getVertexHandle();
		if (vhs.size() != 4) {
			std::cerr << "It is not a tet mesh!\n";
			return 0;
		}
		for (auto& eh : cell.getEdgeHandle()) {
			len_max = std::max(len_max, mesh.getLength(eh));
		}
		double height_min = 999999999;
		for (int i = 0; i < 4; ++i) {
			auto& v = mesh.vertices(vhs[i]);
			std::vector<Vex> f_vs;
			for (int j = 0; j < 4; ++j) {
				if (j == i) continue;
				f_vs.push_back(mesh.vertices(vhs[j]));
			}
			// 平面方程 ax + by + cz + d = 0
			Vec normal = (f_vs[2] - f_vs[0]) % (f_vs[1] - f_vs[0]);
			double d = -(normal.x() * f_vs[0].x() + normal.y() * f_vs[0].y() + normal.z() * f_vs[0].z());
			double num_up = std::abs(v.x() * normal.x() + v.y() * normal.y() + v.z() * normal.z() + d);
			double num_down = normal.norm();
			height_min = std::min(height_min, num_up / num_down);
		}
		double ar = len_max / std::max(height_min, (double)1E-7F);// 避免除以零
		//if (ar < 1.0) return 1;
		//if (ar > 256) {
		//	//std::cout << "Worning: There exist too bad tetrahedron!!!\n";
		//	return 0;
		//}
		//return 1 - (std::log(ar) / std::log(2)) / 8;
		return ar;
	}

}


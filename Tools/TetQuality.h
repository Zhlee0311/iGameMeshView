#pragma once
#include <MeshKernel/Mesh.h>
#include <Eigen/Core>
//#include <omp.h>
#include <time.h>
# define PI acos(-1)
using namespace std;
using namespace MeshKernel;
/*
* 
*四面体指标数据测量 
*/
class TetQuality
{
public:

	 
	TetQuality() {
	}
	/*
	* 计算某一个四面体单元的最小/最大长度
	*/
	static vector<double> GetMinAndMaxLenOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameEdgeHandle>  edgeHandles = cell.getEdgeHandle();
		double minLength = DBL_MAX, maxLength = 0.0;

		for (iGameEdgeHandle eh : edgeHandles) {
			iGameEdge edge = tetMesh.edges(eh);
			double length = (tetMesh.vertices(edge.vh1()) - tetMesh.vertices(edge.vh2())).norm();
			minLength = min(length, minLength);
			maxLength = max(length, maxLength);
		}

		vector<double> result;
		result.push_back(minLength);
		result.push_back(maxLength);

		return  result;
	}


	/*
	* 计算某一个四面体单元的边长比 最长边/最短边
	* 正四面体：1
	*/
	static  double GetEdgeRatioOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		vector<double> result = GetMinAndMaxLenOfCell(cellHandle, tetMesh);
		return  result[1]/result[0];
	}
	 
	/*
	* 计算某一个四面体单元的体积
	*/
	static double GetVolumeOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> vertices;

		for (iGameVertexHandle vh : vhs) {
			vertices.push_back(tetMesh.vertices(vh));
		}

		vector<iGameVertex> L(3);
		L[0] = vertices[1] - vertices[0];
		L[1] = vertices[2] - vertices[0];
		L[2] = vertices[3] - vertices[0];
		double volume = (L[0] % L[1]) * L[2] / 6;
		volume = volume < 0 ? -volume : volume;

		return volume;
	
	}
	
	/*
	* 计算某一个面的面积 
	*/
	static double  GetAreaOfFace(iGameVertex v1, iGameVertex v2, iGameVertex v3) {
		return  ((v2 - v1) % (v3 - v1)).norm() / 2;
	}
	/*
	* 计算某一个四面体单元的面积 该点对应面的面积 
	*/
	static vector<double> GetAreaOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> vertices;
		for (iGameVertexHandle vh : vhs) {
			vertices.push_back(tetMesh.vertices(vh));
		}
		vector<double> areas;

	
		double area = GetAreaOfFace(vertices[1], vertices[2],vertices[3]);
		areas.push_back(area);

		area = GetAreaOfFace(vertices[0], vertices[2],vertices[3]);
		areas.push_back(area);

		area = GetAreaOfFace(vertices[0], vertices[1],vertices[3]);
		areas.push_back(area);

		area = GetAreaOfFace(vertices[0], vertices[1],vertices[2]);
		areas.push_back(area);

		return areas;
	}
	/*
	* 计算某一个四面体单元的内切球的半径  3*volume/sum(area)
	*/
	static double  GetInradiusOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		vector<double> areas = GetAreaOfCell(cellHandle, tetMesh);
	    double volume  = GetVolumeOfCell(cellHandle, tetMesh);
		double sumArea = 0;
		for (double area : areas) {
			sumArea += area;
		}
		return 3.0 * volume / sumArea;
	}
	/*
	* 计算某一个四面体单元的外接球的球心
	*/
	static iGameVertex GetOuterCircle(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		Eigen::Matrix3d m3;
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> v;
		for (iGameVertexHandle vh : vhs) {
			v.push_back(tetMesh.vertices(vh));
		}

		iGameVertex   p1 = (v[1] - v[0]) * 2;
		iGameVertex   p2 = (v[2] - v[1]) * 2;
		iGameVertex   p3 = (v[3] - v[2]) * 2;
		double d1 = v[1] * v[1] - v[0] * v[0];
		double d2 = v[2] * v[2] - v[1] * v[1];
		double d3 = v[3] * v[3] - v[2] * v[2];
		m3 << p1.x(), p1.y(), p1.z(),
			p2.x(), p2.y(), p2.z(),
			p3.x(), p3.y(), p3.z();

		Eigen::Vector3d vc3 = Eigen::Vector3d(d1, d2, d3);
		/*  cout << m3 << endl;
		  cout << vc3 << endl;*/
		Eigen::Matrix3d  m3IN = m3.inverse();

		vc3 = m3IN * vc3;
		return iGameVertex(vc3(0), vc3(1), vc3(2));
	}
	/*
	* 计算某一个四面体单元的外接球的半径
	*/
	static double  GetCircumradiusOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		iGameVertex  vertice = tetMesh.vertices(cell.vh(0));
		iGameVertex outcircle = GetOuterCircle(cellHandle, tetMesh);

		return (vertice - outcircle).norm();
	}

	/*
	* 计算某个四面体的纵横比   最长边/( 2*sqrt(6)*内切半径)   
	* 接受范围：[1,3]
	* 最好：1
	*/
	static double GetAspectRatioOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		double r = GetInradiusOfCell(cellHandle, tetMesh);
		double maxLength = GetMinAndMaxLenOfCell(cellHandle, tetMesh)[1];
 
		double  coff = 2.0 * sqrt(6);
		double aspectRatio = maxLength / coff / r;
		return aspectRatio;
	}

 
	/*
	* 计算某个四面体的雅可比行列式的结果 为 6倍的体积
	* 接受范围：[0,DBL MAX]
	* 单位长度正四面体：sqrt(2)/2
    */
	static double GetJacobianOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		 return GetVolumeOfCell(cellHandle, tetMesh) * 6.0;
	}
 

	/*
	* 计算某个四面体的某点的塌陷率
	*/
	static double  GetCollapseRatioOfVertex(iGameVertex v1, iGameVertex v2, iGameVertex v3, double volume) {
		double area = ((v2 - v1) % (v3 - v1)).norm();
		double high = volume / area * 6;

		double maxLength = max((v2 - v1).norm(), (v3 - v1).norm());
		maxLength = max(maxLength, (v3 - v2).norm());

		return  high / maxLength;
	}
	/*
	* 计算某个四面体的塌陷率   某点所在高 除以 该点对应的面的最长边。
	* 返回四个点的中最小塌陷率
	* 接受范围：[0.1,DBL MAX]
	* 最好：sqrt(6)/3
	*/
	static  double  GetCollapseRatioOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		 double volume = GetVolumeOfCell(cellHandle, tetMesh);
 
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> vertices;
		for (iGameVertexHandle vh : vhs) {
			vertices.push_back(tetMesh.vertices(vh));
		}

		double CollapseRatio = GetCollapseRatioOfVertex(vertices[1], vertices[2], vertices[3], volume);

		CollapseRatio = min(CollapseRatio, GetCollapseRatioOfVertex(vertices[0], vertices[2], vertices[3], volume));
		CollapseRatio = min(CollapseRatio, GetCollapseRatioOfVertex(vertices[1], vertices[0], vertices[3], volume));
		CollapseRatio = min(CollapseRatio, GetCollapseRatioOfVertex(vertices[1], vertices[2], vertices[0], volume));
		return CollapseRatio;
	
	}

 
	/*
	*得到某个四面体体积歪斜度 (外接球的正四面体的体积-体积)/外接球的正四面体的体积
	* 接受范围：[0,1]
	* 最好：0
	*/
	static double GetVolSkewOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		double circumRadius = GetCircumradiusOfCell(cellHandle, tetMesh);
		double a = circumRadius * 4 / sqrt(6);
		 double volume = GetVolumeOfCell(cellHandle, tetMesh);
 
		double regularVolume = a * a * a * sqrt(2) / 12;
		return (regularVolume-volume)/ regularVolume;
	}
 
	/*
	*得到某个四面体的某一点歪斜度   某个节点到对边中点的线段 与 另外两条边中点连接的线段之间 的较小的角
	*/
	static double GetSkewnessOfVertex(iGameVertex v0, iGameVertex v1, iGameVertex v2) {
	 
			iGameVertex	m12 = (v1 + v2) / 2;
			iGameVertex m01 = (v0 + v1) / 2;
			iGameVertex m02 = (v0 + v2) / 2;
			double cosa = (v0 - m01).normalize() * (m01 - m02).normalize();
			double a = acos(cosa) * 180 /   PI;
			return min(a, 180 - a);
	}

	/*
	*得到某个四面体的某个面的歪斜度   为三个点的歪斜度中的最大值  某个节点到对边中点的线段 与 另外两条边中点连接的线段之间 的较小的角
	* 接受范围:(0,90]
	* 最好：90
	*/
	static double GetSkewnessOfFace(iGameFaceHandle faceHandle, MeshKernel::VolumeMesh& tetMesh) {
		double skewOfFace = 0;
		iGameFace face = tetMesh.faces(faceHandle);

		vector<iGameVertexHandle> vhs = face.getVertexHandle();
		vector<iGameVertex> v;
		for (iGameVertexHandle vh : vhs) {
			v.push_back(tetMesh.vertices(vh));
		}

		skewOfFace = max(GetSkewnessOfVertex(v[0], v[1], v[2]), skewOfFace);
		skewOfFace = max(GetSkewnessOfVertex(v[1], v[0], v[2]), skewOfFace);
		skewOfFace = max(GetSkewnessOfVertex(v[2], v[1], v[0]), skewOfFace);
		return skewOfFace;
	}

	/*
	*得到某个四面体的歪斜度  为四个面中歪斜度的最大值  某个节点到对边中点的线段 与 另外两条边中点连接的线段之间 的较小的角
	*/
	/*static double GetSkewnessOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		double  skewOfCell = 0;
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameFaceHandle> fhs = cell.getFaceHandle();

		for (iGameFaceHandle fh : fhs) {
			skewOfCell = max(GetSkewnessOfFace(fh, tetMesh), skewOfCell);
		}

		return skewOfCell;
	}*/
 
	/*
	*得到某个四面体的某个面的的v0的内角
	*/
	static double  GetInternalAnglesOfVertex(iGameVertex v0, iGameVertex v1, iGameVertex v2) {

		double cosa = (v1 - v0).normalize() * (v2 - v0).normalize();
		double angle = acos(cosa) * 180.0 /  PI;

		return angle;
	}
 
	/*
	*得到某个四面体的某个面的三个内角 
	*/
	static vector<double> GetInternalAnglesOfFace(iGameFaceHandle faceHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameFace face = tetMesh.faces(faceHandle);

		vector<iGameVertexHandle> vhs = face.getVertexHandle();
		vector<iGameVertex> v;
		for (iGameVertexHandle vh : vhs) {
			v.push_back(tetMesh.vertices(vh));
		}

		vector<double> angles;
		angles.push_back(GetInternalAnglesOfVertex(v[0], v[1], v[2]));
		angles.push_back(GetInternalAnglesOfVertex(v[1], v[0], v[2]));
		angles.push_back(GetInternalAnglesOfVertex(v[2], v[1], v[0]));
		return angles;
	}

	/*
	*得到某个四面体的所有面的内角  
	*/
	static vector<vector<double>> GetInternalAnglesOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameFaceHandle> fhs = cell.getFaceHandle();
		vector<vector<double>> angles;
		for (int i = 0; i < fhs.size(); i++) {
			angles.push_back(GetInternalAnglesOfFace(fhs[i], tetMesh));
		}
		return angles;
	}

    /*
    *得到某个四面体的最小内角，角度制
    */
    static double GetMinInternalAnglesOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
        iGameCell cell = tetMesh.cells(cellHandle);
        vector<iGameFaceHandle> fhs = cell.getFaceHandle();
        double min_angel = DBL_MAX;
        for (int i = 0; i < fhs.size(); i++) {
            auto angles = GetInternalAnglesOfFace(fhs[i], tetMesh);
            for(auto a : angles){
                min_angel = std::min(min_angel, a);
            }
        }
        return min_angel;
    }
 


	/*
	* 计算某个四面体v0所在的高的长度
	*/
	static double GetHighOfVertex(iGameVertex v0, iGameVertex v1, iGameVertex v2, iGameVertex v3) {
		iGameVertex normOfFace = ((v2 - v1) % (v3 - v1)).normalize();
		return abs(normOfFace * (v0 - v1));
	}

	/*
	* 计算某个四面体的体长宽比   最长边/最短高
	* 单位正四面体：sqrt(3)/2
	*/
	static double GetVolAspectRatioOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {

		double maxLength = GetMinAndMaxLenOfCell(cellHandle,tetMesh)[1];
		double minLength = GetMinAndMaxLenOfCell(cellHandle,tetMesh)[0];
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> vertices;
		for (iGameVertexHandle vh : vhs) {
			vertices.push_back(tetMesh.vertices(vh));
		}

		double minHigh = GetHighOfVertex(vertices[0], vertices[1], vertices[2], vertices[3]);
		minHigh = min(GetHighOfVertex(vertices[1], vertices[0], vertices[2], vertices[3]), minHigh);
		minHigh = min(GetHighOfVertex(vertices[2], vertices[1], vertices[0], vertices[3]), minHigh);
		minHigh = min(GetHighOfVertex(vertices[3], vertices[1], vertices[2], vertices[0]), minHigh);
		return maxLength / minHigh;
	}

	 

	/*
	* 计算所有四面体的等角斜率  max( (Qmax-Qe)/(180-Qe)，(Qe-Qmin)/Qe ) Qmax 最大角 Qmin最小 Qe 60（三角形）或90（四边形） acos(1/3.0)四面体
	* 计算出二面角 求其等角斜率大小
	* 再求所有面中的最大角 和最小角  算出等角斜率
	* 取两者中较大的一个
	* 
	* 最好：0
	*
	*/
	static double GetEquiangleSkewnessOfCell(iGameCellHandle cellHandle, MeshKernel::VolumeMesh& tetMesh) {
		iGameCell cell = tetMesh.cells(cellHandle);
		vector<iGameVertexHandle> vhs = cell.getVertexHandle();
		vector<iGameVertex> vertices;
		for (iGameVertexHandle vh : vhs) {
			vertices.push_back(tetMesh.vertices(vh));
		}

		iGameVertex ab = (vertices[1] - vertices[0]).normalize();
		iGameVertex ac = (vertices[2] - vertices[0]).normalize();
		iGameVertex ad = (vertices[3] - vertices[0]).normalize();
		iGameVertex bc = (vertices[2] - vertices[1]).normalize();
		iGameVertex bd = (vertices[3] - vertices[1]).normalize();
		iGameVertex cd = (vertices[3] - vertices[2]).normalize();

		iGameVertex abc = (bc % ab).normalize();
		iGameVertex abd = (ab % ad).normalize();
		iGameVertex acd = (cd % ad).normalize();
		iGameVertex bcd = (bc % cd).normalize();

		//二面角
		double alpha = acos(-(abc * abd));
		double beta = acos(-(abc * acd));
		double gamma = acos(-(abc * bcd));
		double delta = acos(-(abd * acd));
		double epsilon = acos(-(abd * bcd));
		double zeta = acos(-(acd * bcd));

		double minAngle = alpha;
		minAngle = min(minAngle, beta);
		minAngle = min(minAngle, gamma);
		minAngle = min(minAngle, delta);
		minAngle = min(minAngle, epsilon);
		minAngle = min(minAngle, zeta);

		double maxAngle = alpha;
		maxAngle = min(maxAngle, beta);
		maxAngle = min(maxAngle, gamma);
		maxAngle = min(maxAngle, delta);
		maxAngle = min(maxAngle, epsilon);
		maxAngle = min(maxAngle, zeta);

		double theta = acos(1 / 3.0) * 180.0 / PI;
		minAngle *= 180.0 /  PI;
		maxAngle *= 180.0 /  PI;

		double dihedralMaxSkew = (maxAngle - theta) / (180.0 - theta);
		double dihedralMinSkew = (theta - minAngle) / theta;

		double maxEquiangleSkew = dihedralMaxSkew;
		maxEquiangleSkew = max(maxEquiangleSkew, dihedralMinSkew);

		//面上的内角
		/*double angles[12];

		angles[0] = acos(-(ab * bc));
		angles[1] = acos((bc * ac));
		angles[2] = acos((ac * ab));
		angles[3] = acos(-(ab * bd));
		angles[4] = acos((bd * ad));
		angles[5] = acos((ad * ab));
		angles[6] = acos(-(bc * cd));
		angles[7] = acos((cd * bd));
		angles[8] = acos((bd * bc));
		angles[9] = acos((ad * cd));
		angles[10] = acos(-(cd * ac));
		angles[11] = acos((ac * ad));
		
			minAngle = angles[0];
			maxAngle = angles[1];
			for (int i = 0; i < 12; i++) {
				minAngle = min(minAngle, angles[i]);
				maxAngle = max(maxAngle, angles[i]);
			}

			minAngle *= 180.0 / TET_PI;
			maxAngle *= 180.0 / TET_PI;*/

		vector<vector<double>> anglesOfFaces = GetInternalAnglesOfCell(cellHandle,tetMesh);
		minAngle = anglesOfFaces[0][0];
		maxAngle = anglesOfFaces[0][0];

		for (vector<double> angles : anglesOfFaces) {
			for (double angle : angles) {
				minAngle = min(angle, minAngle);
				maxAngle = max(angle, maxAngle);
			}
		}


		theta = 60.0;
		double maxSkew = (maxAngle - theta) / (180.0 - theta);
		double minSkew = (theta - minAngle) / theta;

		maxEquiangleSkew = max(maxEquiangleSkew, maxSkew);
		maxEquiangleSkew = max(maxEquiangleSkew, minSkew);


		return 	maxEquiangleSkew = max(maxEquiangleSkew, maxSkew);
	
	}
	 
  
private:
 
};


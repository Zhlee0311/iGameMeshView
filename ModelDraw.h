#pragma once
/* 模型渲染类，继承于ViewOpenGL类，传入模型对象，处理模型 */
#include <QtCore/QString>
#include <QtCore/qstring.h>
#include <vector>
#include <QtCore/qstring.h>
#include <QInputDialog>
#include"Surface_Algorithm/Surface_Fairing/Fairing.h"
#include"Surface_Algorithm/Surface_Para/Para.h"

#if __linux__
#include <QtGui>
#else

#include <QtGUI/QtGui>

#endif

#include <QtWidgets/qfiledialog.h>
#include "ViewOpenGL.h"
#include <set>
#include <float.h>

#include <Eigen/Dense>
#include <Eigen/Core>

using namespace std;

class ModelDraw : public ViewOpenGL {
    Q_OBJECT

public:
    ModelDraw(QWidget *parent = 0);

    virtual ~ModelDraw(void);

protected:

    // 模型结构体
    struct Model {
        std::string fileName;   // 文件名
        Structure structure;    // 结构类型：表面网格、体网格
        MeshKernel::SurfaceMesh surfaceMesh;//表面网格
        MeshKernel::VolumeMesh volumeMesh;//体网格
        QMatrix4x4 modelMatrix; // 模型矩阵
        QMatrix4x4 rotateMatrix; // 旋转矩阵
        float modelScale;   // 模型缩放比例
        std::vector<GLfloat> vertices;  // 存贮模型的顶点数据(其中包括三角面片和线框的顶点)，用于传递到显存中进行渲染
        std::vector<GLfloat> pick_vertices; // 存储点选数据
        std::vector<GLfloat> information; // 存储一些数据信息
        std::vector<GLfloat> crossField; // 标架场
        std::vector<GLuint> VAOs, VBOs;  // VAO,VBO数组
        int tri_count;  //绘制的三角形面片数量
        int line_count; //绘制的线段数量
    };
    // 模型列表和当前模型指针
    std::map<int, Model *> modelList;
    Model *currentModel = nullptr;  // 此指针指用来指向当前的模型
    Model *tempModel = nullptr;
    MeshKernel::SurfaceMesh *savedSurfaceMesh = nullptr;    // 此指针相当于网格存档
    MeshKernel::VolumeMesh *savedVolumeMesh = nullptr;    // 此指针相当于网格存档
    int currentNewID = -1;
    int currentModelID = -1;
    int tempModelID = -1;
    bool isCurrentModel = false;

    struct DrawItem {
        // 6个为一组，前三个是坐标，后三个是颜色
        std::vector<GLfloat> point; // 点
        std::vector<GLfloat> edge; // 线
        std::vector<GLfloat> face; // 面
    };
    DrawItem drawItem;

    QString file_suffix;    // 文件名后缀

    GLuint iVAO = 0, iVBO = 0;
    GLuint cVAO = 0, cVBO = 0;    // 坐标系VAO、VBO
    GLuint bVAO = 0, bVBO = 0;  // 背景VAO、VBO
    GLuint cbVAO = 0, cbVBO = 0;  // colorBar VAO、VBO
    std::vector<GLuint> dVAO{0, 0, 0}; // drawItem VAO、VBO
    std::vector<GLuint> dVBO{0, 0, 0};
    std::vector<GLfloat> coord_vertices;    // 坐标系和圆
    std::vector<GLfloat> cutline_vertices;    // 存储切割线顶点数据
    std::vector<MeshKernel::iGameVertexHandle> pickedVHandle;
    std::vector<int> selected_v_indices;
    std::vector<int> selected_e_indices;
    std::vector<int> selected_f_indices;
    std::vector<int> selected_c_indices;

    std::vector<QVector3D> cutVectors;    // 切割平面的两个法向量
    std::set<MeshKernel::iGameFaceHandle> sectionFace;    // 截面
    // deformation固定顶点和移动顶点
    std::vector<std::pair<MeshKernel::iGameVertexHandle, MeshKernel::iGameVertex> > moved_points;
    std::vector<std::pair<MeshKernel::iGameVertexHandle, MeshKernel::iGameVertex> > fixed_points;
    std::vector<std::pair<MeshKernel::iGameVertexHandle, MeshKernel::iGameVertex> > previous_position;

    // 线与点的距离,point1和point2为线段，point0为点
    double point2LineDis(QVector3D point1, QVector3D point2, QVector3D point0);

    // 判断线是否穿过三角形
    bool isIntersectTriangle(QVector3D orig, QVector3D end, QVector3D v0, QVector3D v1, QVector3D v2,
                             QVector3D &intersection);

    // 显示当前模型数据
    std::function<void(void)> showInfo;
    std::function<void(double, double, double)> updatePositionText;
    std::function<std::pair<MeshKernel::iGameVertex, bool>(void)> getPositionText;

public:

    void setShowInfo(std::function<void(void)> info) {
        showInfo = info;
    }

    void setUpdatePositionText(std::function<void(double, double, double)> updatePositionText) {
        this->updatePositionText = updatePositionText;
    }

    void setGetPositionText(std::function<std::pair<MeshKernel::iGameVertex, bool>(void)> getPositionText) {
        this->getPositionText = getPositionText;
    }

    bool isMeshValid() {
        if (!currentModel) return false;
        return true;
    }

    inline Structure getStructure() {
        return currentModel->structure;
    };

    // added by Sheng
    inline int getVertexSize() {
        if (currentModel->structure == SURFACEMESH) return currentModel->surfaceMesh.VertexSize();
        else if (currentModel->structure == VOLUMEMESH) return currentModel->volumeMesh.VertexSize();
        return 0;
    };

    inline int getEdgeSize() {
        if (currentModel->structure == SURFACEMESH) return currentModel->surfaceMesh.EdgeSize();
        else if (currentModel->structure == VOLUMEMESH) return currentModel->volumeMesh.EdgeSize();
        return 0;
    };

    inline int getFaceSize() {
        if (currentModel->structure == SURFACEMESH) return currentModel->surfaceMesh.FaceSize();
        else if (currentModel->structure == VOLUMEMESH) return currentModel->volumeMesh.FaceSize();
        return 0;
    };

    inline bool hasVT() {
        return false;
        //if (Mesh) return this->Mesh->getHasVT();
    };

    inline bool hasVN() {
        return false;
        //if (Mesh) return this->Mesh->getHasVN();
    };

    inline bool hasMesh() {
        return currentModel != nullptr;
    }

    void saveFlieName(std::string fname) {
        currentModel->fileName = fname;
    }

    std::string getFileName() {
        return currentModel->fileName;
    }

    // 当前点选的ID
    int pickedItemHandle = -1;
    std::string pickedItem;

    int getPickedItemHandle(std::string &item) {
        if (!currentModel) return -1;
        item = pickedItem;
        return pickedItemHandle;
    };

    // 点选、切割相关
    void loadPickItemToVBO();

    void loadMeshInformationToVBO();

    void loadCrossFieldToVBO();

    void loadDrawItemToVBO();

    void drawPickItem();

    void drawInformationItem();

    void drawCrossField();

    void drawDrawItem();

    void updateCutMesh();

    // 模型操作相关（加载、保存、删除）
    void changeCurrentMeshToNext();

    void changeCurrentMeshToLast();

    void createModel();

    void deleteModel();

    void meshClear();

    void meshInformationClear();

    void pickedItemClear();

    void informationClear();

    void crossFieldClear();

    void drawItemClear(int);

    bool loadMesh(std::string filename);

    bool saveMesh(std::string filename);

    bool loadHedra(std::string filename);

    bool saveHedra(std::string filename);


    inline bool copyMesh() {
        if (!currentModel) return false;
        if (currentModel->structure == SURFACEMESH) {
            delete savedSurfaceMesh;
            savedSurfaceMesh = nullptr;
            savedSurfaceMesh = new MeshKernel::SurfaceMesh(currentModel->surfaceMesh);
        } else if (currentModel->structure == VOLUMEMESH) {
            delete savedVolumeMesh;
            savedVolumeMesh = nullptr;
            savedVolumeMesh = new MeshKernel::VolumeMesh(currentModel->volumeMesh);
        }
        return true;
    }

    inline bool recoverMesh() {
        if (!savedSurfaceMesh && !savedVolumeMesh) return false;
        if (currentModel->structure == SURFACEMESH) {
            currentModel->surfaceMesh = *new MeshKernel::SurfaceMesh(*savedSurfaceMesh);
        } else if (currentModel->structure == VOLUMEMESH) {
            currentModel->volumeMesh = *new MeshKernel::VolumeMesh(*savedVolumeMesh);
        }
        updateCurrentMesh();
        return true;
    }

    inline bool isTetMesh() {
        return currentModel->structure == VOLUMEMESH;
    }

public:

    void viewCenter();// 视点中心
    void LoadRotation(void);

    void ResetView(void);// 重置视图

    // 不同的编辑模式，供鼠标事件选择
    enum EditModel {
        MODELVIEW, MODELEDIT, PICKITEM, MODELCUT
    };
    EditModel editModel;

    void setEditModel(const EditModel &editmodel) {
        editModel = editmodel;
        switch (editModel) {
            case MODELVIEW: {
                this->setCursor(Qt::SizeAllCursor);
                break;
            }
            case MODELEDIT: {
                this->setCursor(Qt::SizeAllCursor);
                break;
            }
            case PICKITEM: {
                this->setCursor(Qt::PointingHandCursor);
                break;
            }
            case MODELCUT: {
                this->setCursor(Qt::CrossCursor);
                break;
            }
        }
    }

    EditModel getEditModel() {
        return editModel;
    }

    // 点选类型（点、线、面、体）
    enum PickType {
        PickPoint, PickEdge, PickFace, PickCell
    };
    PickType pickType;

    void setPickType(const PickType &pickmode) {
        pickType = pickmode;
    }

    PickType getPickType() {
        return pickType;
    }

    void showMeshNormal();

    void removeSelectedAll();

    // 渲染开关
    bool faceCull = false;  // 面剔除开关
    bool surfaceGrid = true;    //表面网格开关
    bool coordCircle = false;    //坐标圈开关

    void changeSurfaceGrid() {
        surfaceGrid = !surfaceGrid;
        update();
    }

    void changeFaceCull() {
        faceCull = !faceCull;
        update();
    }

    void changeCoordCircle() {
        coordCircle = !coordCircle;
        update();
    }

    void resetView() {
        ViewAll();
        update();
    }

    // 网格切割相关
    bool flag_CutPlane = false;
    double cutX = 0.f, cutY = 0.f, cutZ = 0.f;// 0 全部显示，1 全部不显示
    double minX, minY, minZ, maxX, maxY, maxZ;    // 模型坐标轴下的最大最小值
    double centerX = 0.0, centerY = 0.0, centerZ = 0.0, radius = 1.0f;    // 模型中心点和半径
    void updateCutFlag(bool flag) {
        flag_CutPlane = flag;
        if (flag_CutPlane) updateCutMesh();
        else updateCurrentMesh();
    }

protected:

    void DrawScene();// 绘制模型
    void DrawCoordCircle();// 绘制坐标和圆形
    void DrawBackGround();

    void DrawSceneModel(void);// 传入模型
    void DrawStyle(void);// 绘制样式：点、线、面片、平滑面
    void ColorStyle(void);// 着色样式：模拟光照着色、根据点法向着色

    // 渲染相关
    void updateMeshModel();

    void updateCurrentMesh();

    void loadShader();

    void drawTriMesh();

    void drawQuadMesh();

    // 点选
    void pickItem(double x, double y);

    void pickPoint(double x, double y);

    void pick_point_with_depth(float x, float y, double (&p)[3], double itemPosition[3]);

    QVector2D lineBeginPoint;
    QVector2D lineEndPoint;
    // 点选物体的中心坐标
    double pickedItemPosition[3];

    // 切割
    //void calcCutLine(QVector2D begin, QVector2D end);
    void PickItemTranslate();

    //三角形转四边形的特征边
    std::vector<array<int, 2>> triconstrains;

    //网格合并相关
    int firstMeshFaceSize = -1;
    int firstMeshVertexSize = -1;

    //重写鼠标事件，增加点击操作
    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void wheelEvent(QWheelEvent *);

    void keyPressEvent(QKeyEvent *);

    void keyReleaseEvent(QKeyEvent *);

    // 重写模型旋转、平移、缩放操作
    void Translate(const Vector3d &trans);

    void ViewTranslate(const Vector3d &trans);

    void Rotate(const Vector3d &axis, const double &angle);

    void ModelScale(const Vector3d &trans);

    void PickItemTranslation(const QPoint &p);

public:
    // 网格质量检测类型
    enum MeshMetric {
        OFF,
        TRI_Area,
        TRI_MaxAngle,
        TRI_MinAngle,
        TRI_Jacobian,
        TRI_AspectRatio,
        TRI_EdgeRatio,
        QUAD_Area,
        QUAD_MaxAngle,
        QUAD_MinAngle,
        QUAD_Jacobian,
        QUAD_AspectRatio,
        QUAD_EdgeRatio,
        QUAD_Warpage,
        QUAD_Taper,
        QUAD_Skew,
        TET_Volume,
        TET_AspectRatio,
        TET_Jacobian,
        TET_CollapseRatio,
        TET_Skew,
        TET_InternalAngle,
        TET_VolAspectRatio,
        TET_EquiangleSkew,
        HEX_Volume,
        HEX_Taper,
        HEX_Jacobian,
        HEX_EdgeRatio,
        HEX_MaxEdgeRatio,
        HEX_Skew,
        HEX_Strech,
        HEX_Diagonal,
        HEX_RelativeSizeSquared
    };
    MeshMetric meshMetric = OFF;

    // 网格质量检测并可视化
    void DrawColorBar();

    void paintSurfaceMeshMetric(double &min, double &max, std::vector<double> &values);

    void paintVolumeMeshMetric(double &min, double &max, std::vector<double> &values);

    // 根据输入值返回RGB值，输入值应该满足[0,1]，值越大，代表质量越好
    void valueToRGB(double value, float &R, float &G, float &B);

public:
    void fairing() {
        if (!currentModel || currentModel->structure != SURFACEMESH)return;
        Fairing tmp(currentModel->surfaceMesh, 1e-3);
        tmp.Execute();
        updateCurrentMesh();
    }

    void para() {
        if (!currentModel || currentModel->structure != SURFACEMESH)return;
        Para tmp(currentModel->surfaceMesh);
        tmp.execute();
        updateCurrentMesh();
    }
};
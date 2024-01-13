#pragma once
/*
主窗口类，实现有关界面UI和信号&槽的连接
*/
#include "ui_Turbine_Blade.h"

#if __linux__
#include <QtGui>
#include <QTabWidget>
#else

#include <QtGUI/QtGui>
#include <QtWidgets/Qtabwidget.h>

#endif

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QtWidgets>
#include <string>
#include <QtConcurrent/QtConcurrent>
#include "ModelDraw.h"
#include "UI/ModelListView.h"
#include "UI/MetricChart.h"

class ModelView;

class iGameMeshView : public QMainWindow {
Q_OBJECT
private:
    Ui::MainWindow *ui;
    ModelListView *currentModel;
    int listNum = 0;
    QList<QTreeWidgetItem *> items;
public:
    iGameMeshView(QWidget *parent = Q_NULLPTR);

    ~iGameMeshView(void);

public slots:

    // 表面网格
    bool OpenMesh(void);

    bool SaveMesh(void);

    bool LastMesh(void);

    bool NextMesh(void);

    bool InfoClear(void);

    bool InfoCopy(void);

    bool CopyMesh(void);

    bool RecoverMesh(void);

    bool Fairing(void) {
        ui->openGLWidget->fairing();
        return true;
    }

    bool Para(void){
        ui->openGLWidget->para();
        return true;
    }
    // 体网格
    bool OpenHedra(void);

    bool SaveHedra(void);

    bool ViewStylePoints();    // 渲染样式点
    bool ViewStyleLines();    // 渲染样式线
    bool ViewStyleFill();    // 渲染样式片（平滑）
    bool ViewStyleFlatFill();    // 渲染片（非平滑）
    bool ViewClear();    // 清除模型
    bool ViewLight();    // 灯光渲染
    bool ViewNormal();    // 法线渲染
    bool ViewReset();   // 视角重置
    bool InformationClear();

    bool ChangeSurfaceGrid();

    bool ChangeFaceCull();

    bool ChangeCoordCircle();

    void PrintMeshInfo();

    bool setModelView();

    bool setModelEdit();

    bool setPickItem();

    bool setModelCut();

    bool setPickPoint();

    bool setPickEdge();

    bool setPickFace();

    bool setPickCell();

    bool removeSelectedAll();

    bool cutModel();

    bool ChangeCutFlag();

    bool UpdateCutXYZ();

    bool removeLine();

    //网格质量检测
    void print_tri_metric();

    void print_quad_metric();

    void print_tet_metric();

    void print_hex_metric();


signals:

    bool editOpen();//开启编辑模式

};

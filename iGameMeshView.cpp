#include "iGameMeshView.h"

iGameMeshView::iGameMeshView(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    // 表面网格操作
    connect(ui->btnOpenMesh, SIGNAL(clicked(bool)), this, SLOT(OpenMesh()));
    connect(ui->btnSaveMesh, SIGNAL(clicked(bool)), this, SLOT(SaveMesh()));
    connect(ui->btnLastMesh, SIGNAL(clicked(bool)), this, SLOT(LastMesh()));
    connect(ui->btnNextMesh, SIGNAL(clicked(bool)), this, SLOT(NextMesh()));
    connect(ui->btnLastMesh1, SIGNAL(clicked(bool)), this, SLOT(LastMesh()));
    connect(ui->btnNextMesh1, SIGNAL(clicked(bool)), this, SLOT(NextMesh()));
    connect(ui->btnCopyMesh, SIGNAL(clicked(bool)), this, SLOT(CopyMesh()));
    connect(ui->btnRecoverMesh, SIGNAL(clicked(bool)), this, SLOT(RecoverMesh()));
    connect(ui->btnInfoClear, SIGNAL(clicked(bool)), this, SLOT(InfoClear()));
    connect(ui->btnInfoCopy, SIGNAL(clicked(bool)), this, SLOT(InfoCopy()));

    // 体网格操作
    connect(ui->btnOpenHedra, SIGNAL(clicked(bool)), this, SLOT(OpenHedra()));
    connect(ui->btnSaveHedra, SIGNAL(clicked(bool)), this, SLOT(SaveHedra()));

    // 点选和切割操作
    connect(ui->rtnModelView, SIGNAL(clicked(bool)), this, SLOT(setModelView()));
    connect(ui->rtnModelEdit, SIGNAL(clicked(bool)), this, SLOT(setModelEdit()));
    connect(ui->rtnPickItem, SIGNAL(clicked(bool)), this, SLOT(setPickItem()));
    connect(ui->rtnModelCut, SIGNAL(clicked(bool)), this, SLOT(setModelCut()));
    connect(ui->rtnPickPoint, SIGNAL(clicked(bool)), this, SLOT(setPickPoint()));
    connect(ui->rtnPickEdge, SIGNAL(clicked(bool)), this, SLOT(setPickEdge()));
    connect(ui->rtnPickFace, SIGNAL(clicked(bool)), this, SLOT(setPickFace()));
    connect(ui->rtnPickCell, SIGNAL(clicked(bool)), this, SLOT(setPickCell()));
    connect(ui->btnPickRemoveAll, SIGNAL(clicked(bool)), this, SLOT(removeSelectedAll()));
    connect(ui->btnToCut, SIGNAL(clicked(bool)), this, SLOT(cutModel()));
    connect(ui->btnRemoveLine, SIGNAL(clicked(bool)), this, SLOT(removeLine()));

    //绘制样式
    connect(ui->viewpoints, SIGNAL (clicked(bool)), this, SLOT (ViewStylePoints()));
    connect(ui->viewlines, SIGNAL (clicked(bool)), this, SLOT (ViewStyleLines()));
    connect(ui->viewfill, SIGNAL (clicked(bool)), this, SLOT (ViewStyleFill()));
    connect(ui->viewflatfill, SIGNAL(clicked(bool)), this, SLOT(ViewStyleFlatFill()));
    connect(ui->viewclear, SIGNAL(clicked(bool)), this, SLOT(ViewClear()));
    connect(ui->viewlight, SIGNAL(clicked(bool)), this, SLOT(ViewLight()));
    connect(ui->viewnormal, SIGNAL(clicked(bool)), this, SLOT(ViewNormal()));
    connect(ui->viewReset, SIGNAL(clicked(bool)), this, SLOT(ViewReset()));
    connect(ui->btnInformationClear, SIGNAL(clicked(bool)), this, SLOT(InformationClear()));
    connect(ui->ckbSurfaceGrid, SIGNAL(clicked(bool)), this, SLOT(ChangeSurfaceGrid()));
    connect(ui->ckbFaceCull, SIGNAL(clicked(bool)), this, SLOT(ChangeFaceCull()));
    connect(ui->ckbCoordCircle, SIGNAL(clicked(bool)), this, SLOT(ChangeCoordCircle()));

    //网格算法
    connect(ui->btnSurfaceFairing, SIGNAL(clicked(bool)), this, SLOT(Fairing()));
    connect(ui->btnSurfacePara, SIGNAL(clicked(bool)), this, SLOT(Para()));

    //
    connect(ui->ckbCutPlane, SIGNAL(clicked(bool)), this, SLOT(ChangeCutFlag()));
    connect(ui->cutPlaneX, SIGNAL(valueChanged(int)), this, SLOT(UpdateCutXYZ()));
    connect(ui->cutPlaneY, SIGNAL(valueChanged(int)), this, SLOT(UpdateCutXYZ()));
    connect(ui->cutPlaneZ, SIGNAL(valueChanged(int)), this, SLOT(UpdateCutXYZ()));

    //网格质量检测
    connect(ui->triMeshComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(print_tri_metric()));
    connect(ui->quadMeshComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(print_quad_metric()));
    connect(ui->tetMeshComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(print_tet_metric()));
    connect(ui->hexMeshComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(print_hex_metric()));


    ui->MetricChartWidget->hide();

    // 信息监视器
    ui->openGLWidget->setShowInfo([&]() {
        PrintMeshInfo();
    });

}

iGameMeshView::~iGameMeshView(void) {
}

bool iGameMeshView::OpenMesh(void) {
    // 暂未实现纹理贴图
    QString filePath = QFileDialog::getOpenFileName(this, tr("Load file"), tr(""),
                                                    tr("Obj/Off/Stl/Vtk Files(*.obj *.off *.stl *.vtk)"));
    if (filePath.isEmpty())
        return false;
    else {
        ui->openGLWidget->loadMesh(filePath.toStdString());
        std::string filename = filePath.toStdString();
        int beg = filename.find_last_of('/');
        filePath = QString::fromStdString(filename.substr(++beg, filename.length()));
        QString str = "";
        if (ui->openGLWidget->hasVT()) {
            str += "has VT";
            if (ui->openGLWidget->hasVN()) {
                str += ", has VN";
            } else {
                str += ", no VN";
            }
        } else str += "no VT, no VN";
        ui->info->inputMeshInfo(filePath, ui->openGLWidget->getVertexSize(), ui->openGLWidget->getFaceSize(), str);
        //ui->targetVcnt->setValue(ui->openGLWidget->getVertexSize());
        int vSize = ui->openGLWidget->getVertexSize();
        int eSize = ui->openGLWidget->getEdgeSize();
        int fSize = ui->openGLWidget->getFaceSize();
        currentModel = new ModelListView(filePath, vSize, eSize, fSize);
        items.append(currentModel);
        ui->modelListWidget->addTopLevelItems(items);
        return true;
    }
}

bool iGameMeshView::LastMesh(void) {
    ui->openGLWidget->changeCurrentMeshToLast();
    return true;
}

bool iGameMeshView::NextMesh(void) {
    ui->openGLWidget->changeCurrentMeshToNext();
    return true;
}

bool iGameMeshView::SaveMesh(void) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save model file:"), tr("untitld"),
                                                    tr("Obj File(*.obj);;Off File(*.off);;Stl File(*.stl);;Vtk File(*.vtk)"));
    if (!fileName.isEmpty()) {
        assert(ui->openGLWidget);
        ui->openGLWidget->saveMesh(fileName.toStdString());
        std::string filename = fileName.toStdString();
        int beg = filename.find_last_of('/');
        fileName = QString::fromStdString(filename.substr(++beg, filename.length()));
        ui->info->outputMeshInfo(fileName, ui->openGLWidget->getVertexSize(), ui->openGLWidget->getFaceSize());
        return true;
    }
    return false;
}

bool iGameMeshView::CopyMesh(void) {
    if (ui->openGLWidget->copyMesh()) ui->info->printString("copy mesh success");
    else ui->info->printString("copy mesh fail, triMesh is nullptr");
    return true;
}

bool iGameMeshView::RecoverMesh(void) {
    if (ui->openGLWidget->recoverMesh()) ui->info->printString("recover mesh success");
    else ui->info->printString("recover mesh fail, copyTriMesh is nullptr");
    return true;
}

bool iGameMeshView::InfoClear(void) {
    ui->info->clear();
    return true;
}

bool iGameMeshView::InfoCopy(void) {
    ui->info->printString("The function is not implemented yet.");
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool iGameMeshView::OpenHedra(void) {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Load file"), tr(""), tr("Mesh/Vtk Files(*.mesh *.vtk)"));
    if (filePath.isEmpty())
        return false;
    else {
        ui->openGLWidget->loadHedra(filePath.toStdString());
        std::string filename = filePath.toStdString();
        int beg = filename.find_last_of('/');
        filePath = QString::fromStdString(filename.substr(++beg, filename.length()));
        QString str = "";
        if (ui->openGLWidget->hasVT()) {
            str += "has VT";
            if (ui->openGLWidget->hasVN()) {
                str += ", has VN";
            } else {
                str += ", no VN";
            }
        } else str += "no VT, no VN";
        ui->info->inputMeshInfo(filePath, ui->openGLWidget->getVertexSize(), ui->openGLWidget->getFaceSize(), str);
        //ui->targetVcnt->setValue(ui->openGLWidget->getVertexSize());
        return true;
    }
}

bool iGameMeshView::SaveHedra(void) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save model file:"), tr("untitld"),
                                                    tr("Mesh File(*.mesh)"));
    if (!fileName.isEmpty()) {
        assert(ui->openGLWidget);
        ui->openGLWidget->saveHedra(fileName.toStdString());
        std::string filename = fileName.toStdString();
        int beg = filename.find_last_of('/');
        fileName = QString::fromStdString(filename.substr(++beg, filename.length()));
        ui->info->outputMeshInfo(fileName, ui->openGLWidget->getVertexSize(), ui->openGLWidget->getFaceSize());
        return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool iGameMeshView::ViewStylePoints() {
    ui->openGLWidget->SetDrawMode(ModelDraw::POINTS);
    ui->openGLWidget->makeCurrent();
    return true;
}

bool iGameMeshView::ViewStyleLines() {
    ui->openGLWidget->SetDrawMode(ModelDraw::FLATLINES);
    ui->openGLWidget->makeCurrent();
    return true;
}

bool iGameMeshView::ViewStyleFill() {
    ui->openGLWidget->SetDrawMode(ModelDraw::FILL);
    ui->openGLWidget->makeCurrent();
    return true;
}

bool iGameMeshView::ViewStyleFlatFill() {
    ui->openGLWidget->SetDrawMode(ModelDraw::FLATFILL);
    ui->openGLWidget->makeCurrent();
    return true;
}

bool iGameMeshView::ViewClear() {
    ui->openGLWidget->meshClear();
    //items.count(currentModel);
    //items.erase(items.begin() + currentNum);
    return true;
}

bool iGameMeshView::InformationClear() {

    bool input_ok = false;
    QStringList functions = {"[Select items to clear:]",
                             "All Information",
                             "Picked Item",
                             "Information",
                             "CrossField",
                             "drawItem All",
                             "drawItem point",
                             "drawItem edge",
                             "drawItem face"
    };
    QString func = QInputDialog::getItem(this, " Functions ", " Please select item ", functions, 0, false, &input_ok);
    if (!input_ok) return false;

    if (func == "All Information") {
        ui->openGLWidget->meshInformationClear();
    } else if (func == "Picked Item") {
        ui->openGLWidget->pickedItemClear();
    } else if (func == "Information") {
        ui->openGLWidget->informationClear();
    } else if (func == "CrossField") {
        ui->openGLWidget->crossFieldClear();
    } else if (func == "drawItem All") {
        ui->openGLWidget->drawItemClear(0);
    } else if (func == "drawItem point") {
        ui->openGLWidget->drawItemClear(1);
    } else if (func == "drawItem edge") {
        ui->openGLWidget->drawItemClear(2);
    } else if (func == "drawItem face") {
        ui->openGLWidget->drawItemClear(3);
    }

    QString str = "Test action execute success.";
    ui->info->printString(str);
    return true;

}

bool iGameMeshView::ViewLight() {
    ui->openGLWidget->SetColorMode(ModelDraw::LIGHT);
    return true;
}

bool iGameMeshView::ViewNormal() {
    //ui->openGLWidget->SetColorMode(ModelDraw::NORMAL);
    ui->openGLWidget->showMeshNormal();
    return true;
}

bool iGameMeshView::ViewReset() {
    ui->openGLWidget->resetView();
    ui->info->printString("Reset View");
    return true;
}

bool iGameMeshView::ChangeSurfaceGrid() {
    ui->openGLWidget->changeSurfaceGrid();
    return true;
}

bool iGameMeshView::ChangeFaceCull() {
    ui->openGLWidget->changeFaceCull();
    return true;
}

bool iGameMeshView::ChangeCoordCircle() {
    ui->openGLWidget->changeCoordCircle();
    return true;
}

void iGameMeshView::PrintMeshInfo() {
    if (!ui->openGLWidget->isMeshValid()) {
        stringstream info;
        info.clear();
        std::string m = info.str();
        ui->showInformation->setText(QString::fromStdString(m));
        return;
    }
    stringstream info;
    info.clear();
    info << ui->openGLWidget->getFileName() << '\n';
    std::string m = info.str();
    ui->showInformation->setText(QString::fromStdString(m));
    info.clear();
    int v = ui->openGLWidget->getVertexSize();
    info << "vertices size: " << v << '\n';
    m = info.str();
    ui->showInformation->setText(QString::fromStdString(m));
    info.clear();
    v = ui->openGLWidget->getEdgeSize();
    info << "edges size: " << v << '\n';
    m = info.str();
    ui->showInformation->setText(QString::fromStdString(m));
    info.clear();
    v = ui->openGLWidget->getFaceSize();
    info << "faces size: " << v << '\n';
    m = info.str();
    ui->showInformation->setText(QString::fromStdString(m));
    if (ui->openGLWidget->getEditModel() == ModelDraw::PICKITEM) {
        info.clear();
        std::string pickItem;
        v = ui->openGLWidget->getPickedItemHandle(pickItem);
        if (v != -1) {
            info << (std::string) "picked " << pickItem << " handle: " << v << '\n';
        }
        m = info.str();
        ui->showInformation->setText(QString::fromStdString(m));
    }
}

bool iGameMeshView::setModelView() {
    ui->openGLWidget->setEditModel(ModelDraw::MODELVIEW);
    ui->info->printString(
            "Edit Mode: Model View, LeftButton: ViewRotate, RightButton: ViewTranslate, MouseWheel: ViewScale");
    return true;
}

bool iGameMeshView::setModelEdit() {
    ui->openGLWidget->setEditModel(ModelDraw::MODELEDIT);
    ui->info->printString(
            "Edit Mode: Model Edit, LeftButton: ModelRotate, RightButton: ModelTranslate, MouseWheel: ModelScale");
    return true;
}

bool iGameMeshView::setPickItem() {
    ui->openGLWidget->setEditModel(ModelDraw::PICKITEM);
    ui->info->printString("Edit Mode: Pick Item");
    return true;
}

bool iGameMeshView::setModelCut() {
    ui->openGLWidget->setEditModel(ModelDraw::MODELCUT);
    ui->info->printString("Edit Mode: Model Cut");
    return true;
}

//bool iGameMeshView::setDeformation() {
//	ui->openGLWidget->setEditModel(ModelDraw::DEFORMATION);
//	ui->info->printString("Edit Mode: Deformation");
//	return true;
//}

bool iGameMeshView::setPickPoint() {
    ui->openGLWidget->setPickType(ModelDraw::PickPoint);
    ui->info->printString("Pick : Point");
    return true;
}

bool iGameMeshView::setPickEdge() {
    ui->openGLWidget->setPickType(ModelDraw::PickEdge);
    ui->info->printString("Pick : Edge");
    update();
    return true;
}

bool iGameMeshView::setPickFace() {
    ui->openGLWidget->setPickType(ModelDraw::PickFace);
    ui->info->printString("Pick : Face");
    return true;
}

bool iGameMeshView::setPickCell() {
    ui->openGLWidget->setPickType(ModelDraw::PickCell);
    ui->info->printString("Pick : Cell");
    return true;
}

bool iGameMeshView::removeSelectedAll() {
    ui->openGLWidget->removeSelectedAll();
    return true;
}

bool iGameMeshView::cutModel() {
    //ui->openGLWidget->toCutModel();
    return true;
}

bool iGameMeshView::removeLine() {
    //ui->openGLWidget->removeCutLine();
    return true;
}

bool iGameMeshView::ChangeCutFlag() {
    if (ui->ckbCutPlane->isChecked()) {
        ui->info->printString("enable cut plane");
        UpdateCutXYZ();// 会自动更新 drawdata
    } else {
        ui->info->printString("disable cut plane");
        ui->openGLWidget->updateCutFlag(false);
    }
    update();
    return true;
}

bool iGameMeshView::UpdateCutXYZ() {
    ui->openGLWidget->cutX = (ui->cutPlaneX->value() / 100.f);
    ui->openGLWidget->cutY = (ui->cutPlaneY->value() / 100.f);
    ui->openGLWidget->cutZ = (ui->cutPlaneZ->value() / 100.f);
    if (ui->ckbCutPlane->isChecked()) ui->openGLWidget->updateCutFlag(true);
    else ui->openGLWidget->updateCutFlag(false);
    printf("cut rate: %.2f, %.2f, %.2f\n", ui->openGLWidget->cutX, ui->openGLWidget->cutY, ui->openGLWidget->cutZ);
    //ui->info->printString("update cut plane success");
    return true;
}

//=============================网格质量检测==============================//

void iGameMeshView::print_tri_metric() {
    if (!ui->openGLWidget->hasMesh()) return;
    if (ui->openGLWidget->getStructure() != ViewOpenGL::SURFACEMESH) return;
    string acceptableRange;
    string metricName;
    switch (ui->triMeshComboBox->currentIndex()) {
        case 0: {
            ui->openGLWidget->meshMetric = ModelDraw::OFF;
            break;
        }
        case 1: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_Area;
            acceptableRange = "acceptable range: [0, MAX]";
            metricName = "Area";
            break;
        }
        case 2: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_MaxAngle;
            acceptableRange = "acceptable range: [60, 90]\nOptimal Value: 60";
            metricName = "MaxAngle";
            break;
        }
        case 3: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_MinAngle;
            acceptableRange = "Acceptable Range: [30, 60]\nOptimal Value: 60";
            metricName = "MinAngle";
            break;
        }
        case 4: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_Jacobian;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: 1";
            metricName = "Jacobian";
            break;
        }
        case 5: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_AspectRatio;
            acceptableRange = "Acceptable Range: [1, 1.3]\nOptimal Value: 1";
            metricName = "AspectRatio";
            break;
        }
        case 6: {
            ui->openGLWidget->meshMetric = ModelDraw::TRI_EdgeRatio;
            acceptableRange = "Acceptable Range: [1, 1.3]\nOptimal Value: 1";
            metricName = "EdgeRatio";
            break;
        }
    }
    double min, max;
    std::vector<double> values;
    ui->openGLWidget->paintSurfaceMeshMetric(min, max, values);

    stringstream info;
    info << acceptableRange << '\n' << "Max Value: " << max << '\n' << "Min Value: " << min;
    std::string m = info.str();
    ui->labelTriMetric->setText(QString::fromStdString(m));
    if (ui->openGLWidget->meshMetric == ModelDraw::OFF) ui->MetricChartWidget->hide();
    else {
        ui->MetricChartWidget->show();
        ui->MetricChartWidget->LoadData(metricName, values);
    }
}

void iGameMeshView::print_quad_metric() {
    if (!ui->openGLWidget->hasMesh()) return;
    if (ui->openGLWidget->getStructure() != ViewOpenGL::SURFACEMESH) return;
    string acceptableRange;
    string metricName;
    switch (ui->quadMeshComboBox->currentIndex()) {
        case 0: {
            ui->openGLWidget->meshMetric = ModelDraw::OFF;
            break;
        }
        case 1: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_Area;
            acceptableRange = "acceptable range: [0, MAX]";
            metricName = "Area";
            break;
        }
        case 2: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_MaxAngle;
            acceptableRange = "acceptable range: [90,135]\nOptimal Value: 90";
            metricName = "MaxAngle";
            break;
        }
        case 3: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_MinAngle;
            acceptableRange = "Acceptable Range: [45, 90]\nOptimal Value: 90";
            metricName = "MinAngle";
            break;
        }
        case 4: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_Jacobian;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: 1";
            metricName = "Jacobian";
            break;
        }
        case 5: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_AspectRatio;
            acceptableRange = "Acceptable Range: [1, 1.3]\nOptimal Value: 1";
            metricName = "AspectRatio";
            break;
        }
        case 6: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_EdgeRatio;
            acceptableRange = "Acceptable Range: [1, 1.3]\nOptimal Value: 1";
            metricName = "EdgeRatio";
            break;
        }
        case 7: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_Warpage;
            acceptableRange = "Acceptable Range: [0, 0.7]\nOptimal Value: 0";
            metricName = "Warpage";
            break;
        }
        case 8: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_Taper;
            acceptableRange = "Acceptable Range: [0, 0.7]\nOptimal Value: 0";
            metricName = "Taper";
            break;
        }
        case 9: {
            ui->openGLWidget->meshMetric = ModelDraw::QUAD_Skew;
            acceptableRange = "Acceptable Range: [0.5, 1]\nOptimal Value: 1";
            metricName = "Skew";
            break;
        }
    }
    double min, max;
    std::vector<double> values;
    ui->openGLWidget->paintSurfaceMeshMetric(min, max, values);

    stringstream info;
    info << acceptableRange << '\n' << "Max Value: " << max << '\n' << "Min Value: " << min;
    std::string m = info.str();
    ui->labelQuadMetric->setText(QString::fromStdString(m));
    if (ui->openGLWidget->meshMetric == ModelDraw::OFF) ui->MetricChartWidget->hide();
    else {
        ui->MetricChartWidget->show();
        ui->MetricChartWidget->LoadData(metricName, values);
    }
}

void iGameMeshView::print_tet_metric() {
    if (!ui->openGLWidget->hasMesh()) return;
    if (ui->openGLWidget->getStructure() != ViewOpenGL::VOLUMEMESH) return;
    string acceptableRange;
    string metricName;
    switch (ui->tetMeshComboBox->currentIndex()) {
        case 0: {
            ui->openGLWidget->meshMetric = ModelDraw::OFF;
            break;
        }
        case 1: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_Volume;
            acceptableRange = "acceptable range: [0, MAX]";
            metricName = "Volume";
            break;
        }
        case 2: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_AspectRatio;
            acceptableRange = "acceptable range: [1,3]\nOptimal Value: 1";
            metricName = "AspectRatio";
            break;
        }
        case 3: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_Jacobian;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: sqrt(2)/2";
            metricName = "Jacobian";
            break;
        }
        case 4: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_CollapseRatio;
            acceptableRange = "Acceptable Range: [0.1, MAX]\nOptimal Value: sqrt(6)/3";
            metricName = "CollapseRatio";
            break;
        }
        case 5: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_Skew;
            acceptableRange = "Acceptable Range: [0, 90]\nOptimal Value: 90";
            metricName = "Skew";
            break;
        }
        case 6: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_InternalAngle;
            acceptableRange = "Acceptable Range: [0, 60]\nOptimal Value: 60";
            metricName = "InternalAngle";
            break;
        }
        case 7: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_VolAspectRatio;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: sqrt(3)/2";
            metricName = "Volume AspectRatio";
            break;
        }
        case 8: {
            ui->openGLWidget->meshMetric = ModelDraw::TET_EquiangleSkew;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: 0";
            metricName = "EquiangleSkew";
            break;
        }
    }
    double min, max;
    std::vector<double> values;
    ui->openGLWidget->paintVolumeMeshMetric(min, max, values);

    stringstream info;
    info << acceptableRange << '\n' << "Max Value: " << max << '\n' << "Min Value: " << min;
    std::string m = info.str();
    ui->labelTetMetric->setText(QString::fromStdString(m));
    if (ui->openGLWidget->meshMetric == ModelDraw::OFF) ui->MetricChartWidget->hide();
    else {
        ui->MetricChartWidget->show();
        ui->MetricChartWidget->LoadData(metricName, values);
    }
}

void iGameMeshView::print_hex_metric() {
    if (!ui->openGLWidget->hasMesh()) return;
    if (ui->openGLWidget->getStructure() != ViewOpenGL::VOLUMEMESH) return;
    string acceptableRange;
    string metricName;
    switch (ui->hexMeshComboBox->currentIndex()) {
        case 0: {
            ui->openGLWidget->meshMetric = ModelDraw::OFF;
            break;
        }
        case 1: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Volume;
            acceptableRange = "acceptable range: [0, MAX]";
            metricName = "Volume";
            break;
        }
        case 2: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Taper;
            acceptableRange = "acceptable range: [0, 0.5]\nOptimal Value: 0";
            metricName = "Taper";
            break;
        }
        case 3: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Jacobian;
            acceptableRange = "Acceptable Range: [0, MAX]\nOptimal Value: 1";
            metricName = "Jacobian";
            break;
        }
        case 4: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_EdgeRatio;
            acceptableRange = "Acceptable Range: [1, MAX]\nOptimal Value: 1";
            metricName = "EdgeRatio";
            break;
        }
        case 5: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_MaxEdgeRatio;
            acceptableRange = "Acceptable Range: [1, 1.3]\nOptimal Value: 1";
            metricName = "MaxEdgeRatio";
            break;
        }
        case 6: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Skew;
            acceptableRange = "Acceptable Range: [0, 0.5]\nOptimal Value: 0";
            metricName = "Skew";
            break;
        }
        case 7: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Strech;
            acceptableRange = "Acceptable Range: [0.25, 1]\nOptimal Value: 1";
            metricName = "Strech";
            break;
        }
        case 8: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_Diagonal;
            acceptableRange = "Acceptable Range: [0.65, 1]\nOptimal Value: 1";
            metricName = "Diagonal";
            break;
        }
        case 9: {
            ui->openGLWidget->meshMetric = ModelDraw::HEX_RelativeSizeSquared;
            acceptableRange = "Acceptable Range: [0, 1]";
            metricName = "RelativeSizeSquared";
            break;
        }
    }
    double min, max;
    std::vector<double> values;
    ui->openGLWidget->paintVolumeMeshMetric(min, max, values);

    stringstream info;
    info << acceptableRange << '\n' << "Max Value: " << max << '\n' << "Min Value: " << min;
    std::string m = info.str();
    ui->labelHexMetric->setText(QString::fromStdString(m));
    if (ui->openGLWidget->meshMetric == ModelDraw::OFF) ui->MetricChartWidget->hide();
    else {
        ui->MetricChartWidget->show();
        ui->MetricChartWidget->LoadData(metricName, values);
    }

}




/********************************************************************************
** Form generated from reading UI file 'Turbine_Blade.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURBINE_BLADE_H
#define UI_TURBINE_BLADE_H

#include <ModelDraw.h>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <UI/MetricChart.h>
#include <UI/PrintInfo.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *SurfaceGridSwitch;
    QAction *actiona;
    QAction *actionb;
    QAction *actiondaoch;
    QAction *actionc;
    QAction *actionzanchun;
    QAction *actionzairu;
    QAction *actiontritoquad;
    QAction *actiontritotet;
    QAction *actionMeshSimplification;
    QAction *actionMeshRemesh;
    QAction *actionMeshAddNoise;
    QAction *actionMeshSmooth;
    QAction *actionSubdivision;
    QAction *actionMinimalSurface;
    QAction *actionLSCM;
    QAction *actionBFF;
    QAction *actionMeshFix;
    QAction *actionCADRemeshing;
    QAction *actionRevertNormal;
    QAction *actionCloseMesh;
    QAction *actionTetSimplification;
    QAction *actionMotorcycleGraphs;
    QAction *actionBoolean;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_11;
    QTabWidget *funcTab;
    QWidget *TriMesh;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *verticalLayout_19;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_10;
    QPushButton *btnOpenMesh;
    QPushButton *btnSaveMesh;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnSurfaceFairing;
    QPushButton *btnSurfacePara;
    QPushButton *btnCopyMesh;
    QPushButton *btnRecoverMesh;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_21;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_33;
    QPushButton *btnOpenHedra;
    QPushButton *btnSaveHedra;
    QSpacerItem *verticalSpacer_9;
    QWidget *tab3;
    QVBoxLayout *verticalLayout_23;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_22;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout_27;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnLastMesh;
    QPushButton *btnNextMesh;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnInfoClear;
    QPushButton *btnInfoCopy;
    QGroupBox *groupBox_13;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_13;
    QRadioButton *rtnModelView;
    QRadioButton *rtnModelEdit;
    QSpacerItem *verticalSpacer_4;
    QRadioButton *rtnPickItem;
    QSpacerItem *verticalSpacer_5;
    QRadioButton *rtnModelCut;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_13;
    QRadioButton *rtnPickPoint;
    QRadioButton *rtnPickEdge;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *rtnPickFace;
    QRadioButton *rtnPickCell;
    QPushButton *btnPickRemoveAll;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_14;
    QPushButton *btnToCut;
    QPushButton *btnRemoveLine;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *ckbCutPlane;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_2;
    QSlider *cutPlaneX;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_3;
    QSlider *cutPlaneY;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_4;
    QSlider *cutPlaneZ;
    QWidget *tab;
    QVBoxLayout *verticalLayout_36;
    QGroupBox *groupBox_16;
    QVBoxLayout *verticalLayout_28;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *triMeshComboBox;
    QLabel *labelTriMetric;
    QGroupBox *groupBox_19;
    QVBoxLayout *verticalLayout_32;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QComboBox *quadMeshComboBox;
    QLabel *labelQuadMetric;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_31;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QComboBox *tetMeshComboBox;
    QLabel *labelTetMetric;
    QGroupBox *groupBox_17;
    QVBoxLayout *verticalLayout_30;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QComboBox *hexMeshComboBox;
    QLabel *labelHexMetric;
    QSpacerItem *verticalSpacer_2;
    QTreeWidget *modelListWidget;
    QHBoxLayout *horizontalLayout_17;
    QWidget *viewBox;
    QVBoxLayout *verticalLayout_25;
    QHBoxLayout *horizontalLayout_10;
    MetricChart *MetricChartWidget;
    QVBoxLayout *verticalLayout_37;
    ModelDraw *openGLWidget;
    QHBoxLayout *horizontalLayout_18;
    QDockWidget *outputWidget_2;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_29;
    QLabel *showInformation;
    QDockWidget *outputWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_6;
    PrintInfo *info;
    QVBoxLayout *verticalLayout_4;
    QPushButton *ckbSurfaceGrid;
    QPushButton *ckbCoordCircle;
    QPushButton *ckbFaceCull;
    QFrame *line;
    QPushButton *viewpoints;
    QPushButton *viewlines;
    QPushButton *viewfill;
    QPushButton *viewflatfill;
    QPushButton *viewlight;
    QPushButton *viewnormal;
    QFrame *line_3;
    QPushButton *viewReset;
    QFrame *line_2;
    QPushButton *btnInformationClear;
    QPushButton *btnLastMesh1;
    QPushButton *btnNextMesh1;
    QPushButton *viewclear;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusbar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1213, 863);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Ticon/Resources/iGameLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QPalette{background:#444444;}*{outline:0px;color:#DCDCDC;}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #F0F0D0;\n"
"    background-color: #323232;\n"
"    border: 0px solid #32414B;\n"
"    padding: 0px;\n"
"    selection-background-color: #1464A0;\n"
"    selection-color: #F0F0F0;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QWidget[form=\"true\"],QLabel[frameShape=\"1\"]{\n"
"border:1px solid #242424;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"QWidget[form=\"bottom\"]{\n"
"background:#484848;\n"
"}\n"
"\n"
"QWidget[form=\"bottom\"] .QFrame{\n"
"border:1px solid #DCDCDC;\n"
"}\n"
"\n"
"QWidget[form=\"bottom\"] QLabel,QWidget[form=\"title\"] QLabel{\n"
"border-radius:0px;\n"
"color:#DCDCDC;\n"
"background:none;\n"
"border-style:none;\n"
""
                        "}\n"
"\n"
"QWidget[form=\"title\"],QWidget[nav=\"left\"],QWidget[nav=\"top\"] QAbstractButton{\n"
"border-style:none;\n"
"border-radius:0px;\n"
"padding:5px;\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QWidget[nav=\"top\"] QAbstractButton:hover,QWidget[nav=\"top\"] QAbstractButton:pressed,QWidget[nav=\"top\"] QAbstractButton:checked{\n"
"border-style:solid;\n"
"border-width:0px 0px 2px 0px;\n"
"padding:4px 4px 2px 4px;\n"
"border-color:#00BB9E;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton{\n"
"border-radius:0px;\n"
"color:#DCDCDC;\n"
"background:none;\n"
"border-style:none;\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton:hover{\n"
"color:#FFFFFF;\n"
"background-color:#00BB9E;\n"
"}\n"
"\n"
"QWidget[nav=\"left\"] QAbstractButton:checked,QWidget[nav=\"left\"] QAbstractButton:pressed{\n"
"color:#DCDCDC;\n"
"border-style:solid"
                        ";\n"
"border-width:0px 0px 0px 2px;\n"
"padding:4px 4px 4px 2px;\n"
"border-color:#00BB9E;\n"
"background-color:#444444;\n"
"}\n"
"\n"
"QWidget[video=\"true\"] QLabel{\n"
"color:#DCDCDC;\n"
"border:1px solid #242424;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QWidget[video=\"true\"] QLabel:focus{\n"
"border:1px solid #00BB9E;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QLineEdit,QTextEdit,QPlainTextEdit,QSpinBox,QDoubleSpinBox,QComboBox,QDateEdit,QTimeEdit,QDateTimeEdit{\n"
"border:1px solid #242424;\n"
"border-radius:3px;\n"
"padding:2px;\n"
"background:none;\n"
"selection-background-color:#484848;\n"
"selection-color:#DCDCDC;\n"
"}\n"
"\n"
"QLineEdit:focus,QTextEdit:focus,QPlainTextEdit:focus,QSpinBox:focus,QDoubleSpinBox:focus,QComboBox:focus,QDateEdit:focus,QTimeEdit:focus,QDateTimeEdit:focus,QLineEdit:hover,QTextEdit:hover,QPlainTextEdit:hover,QSpinBox:hover,QDoubleSpinBox:hov"
                        "er,QComboBox:hover,QDateEdit:hover,QTimeEdit:hover,QDateTimeEdit:hover{\n"
"border:1px solid #242424;\n"
"}\n"
"\n"
"QLineEdit[echoMode=\"2\"]{\n"
"lineedit-password-character:9679;\n"
"}\n"
"\n"
".QFrame{\n"
"border:1px solid #242424;\n"
"border-radius:3px;\n"
"}\n"
"\n"
".QGroupBox{\n"
"border:1px solid #242424;\n"
"border-radius:5px;\n"
"margin-top:2ex;\n"
"}\n"
"\n"
".QGroupBox::title{\n"
"subcontrol-origin:margin;\n"
"position:relative;\n"
"left:10px;\n"
"}\n"
"\n"
".QPushButton,.QToolButton{\n"
"border-style:none;\n"
"border:1px solid #242424;\n"
"color:#DCDCDC;\n"
"padding:5px;\n"
"min-height:13px;\n"
"border-radius:4px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
".QPushButton:hover,.QToolButton:hover{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
".QPushButton:pressed,.QToolButton:pressed{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #3838"
                        "38);\n"
"}\n"
"\n"
".QToolButton::menu-indicator{\n"
"image:None;\n"
"}\n"
"\n"
"QToolButton#btnMenu,QPushButton#btnMenu_Min,QPushButton#btnMenu_Max,QPushButton#btnMenu_Close{\n"
"border-radius:3px;\n"
"color:#DCDCDC;\n"
"padding:3px;\n"
"margin:0px;\n"
"background:none;\n"
"border-style:none;\n"
"}\n"
"\n"
"QToolButton#btnMenu:hover,QPushButton#btnMenu_Min:hover,QPushButton#btnMenu_Max:hover{\n"
"color:#FFFFFF;\n"
"margin:1px 1px 2px 1px;\n"
"background-color:rgba(51,127,209,230);\n"
"}\n"
"\n"
"QPushButton#btnMenu_Close:hover{\n"
"color:#FFFFFF;\n"
"margin:1px 1px 2px 1px;\n"
"background-color:rgba(238,0,0,128);\n"
"}\n"
"\n"
"QRadioButton::indicator{\n"
"width:15px;\n"
"height:15px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked{\n"
"image:url(:/Ticon/psblack/radiobutton_unchecked.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked:disabled{\n"
"image:url(:/Ticon/psblack/radiobutton_unchecked_disable.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked{\n"
"image:url(:/Ticon/psblack/radiobutton_chec"
                        "ked.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked:disabled{\n"
"image:url(:/Ticon/psblack/radiobutton_checked_disable.png);\n"
"}\n"
"\n"
"QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{\n"
"padding:0px -3px 0px 3px;\n"
"}\n"
"\n"
"QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{\n"
"width:13px;\n"
"height:13px;\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked,QGroupBox::indicator:unchecked,QTreeWidget::indicator:unchecked,QListWidget::indicator:unchecked{\n"
"image:url(:/Ticon/psblack/checkbox_unchecked.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:unchecked:disabled,QGroupBox::indicator:unchecked:disabled,QTreeWidget::indicator:unchecked:disabled,QListWidget::indicator:disabled{\n"
"image:url(:/Ticon/psblack/checkbox_unchecked_disable.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:checked,QGroupBox::indicator:checked,QTreeWidget::indicator:checked,QListWidget::indicator:checked{\n"
"image:url(:/Ticon/psblack/checkbox_checked.png);\n"
"}\n"
"\n"
"QCheckB"
                        "ox::indicator:checked:disabled,QGroupBox::indicator:checked:disabled,QTreeWidget::indicator:checked:disabled,QListWidget::indicator:checked:disabled{\n"
"image:url(:/Ticon/psblack/checkbox_checked_disable.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate,QGroupBox::indicator:indeterminate,QTreeWidget::indicator:indeterminate,QListWidget::indicator:indeterminate{\n"
"image:url(:/Ticon/psblack/checkbox_parcial.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:indeterminate:disabled,QGroupBox::indicator:indeterminate:disabled,QTreeWidget::indicator:indeterminate:disabled,QListWidget::indicator:indeterminate:disabled{\n"
"image:url(:/Ticon/psblack/checkbox_parcial_disable.png);\n"
"}\n"
"\n"
"QTimeEdit::up-button,QDateEdit::up-button,QDateTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button{\n"
"image:url(:/Ticon/psblack/add_top.png);\n"
"width:10px;\n"
"height:10px;\n"
"padding:1px 5px 0px 0px;\n"
"}\n"
"\n"
"QTimeEdit::down-button,QDateEdit::down-button,QDateTimeEdit::down-button,QDoubleSpinBox::down-"
                        "button,QSpinBox::down-button{\n"
"image:url(:/Ticon/psblack/add_bottom.png);\n"
"width:10px;\n"
"height:10px;\n"
"padding:1px 5px 0px 0px;\n"
"}\n"
"\n"
"QTimeEdit::up-button:pressed,QDateEdit::up-button:pressed,QDateTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{\n"
"top:-2px;\n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDateEdit::down-button:pressed,QDateTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"bottom:-2px;\n"
"}\n"
"\n"
"QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{\n"
"image:url(:/Ticon/psblack/add_bottom.png);\n"
"width:10px;\n"
"height:10px;\n"
"right:2px;\n"
"}\n"
"\n"
"QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{\n"
"subcontrol-origin:padding;\n"
"subcontrol-position:top right;\n"
"width:15px;\n"
"border-lef"
                        "t-width:0px;\n"
"border-left-style:solid;\n"
"border-top-right-radius:3px;\n"
"border-bottom-right-radius:3px;\n"
"border-left-color:#242424;\n"
"}\n"
"\n"
"QComboBox::drop-down:on{\n"
"top:1px;\n"
"}\n"
"\n"
"QMenuBar::item{\n"
"color:#DCDCDC;\n"
"background-color:#484848;\n"
"margin:0px;\n"
"padding:3px 10px;\n"
"}\n"
"\n"
"QMenu,QMenuBar,QMenu:disabled,QMenuBar:disabled{\n"
"color:#DCDCDC;\n"
"background-color:#484848;\n"
"border:1px solid #242424;\n"
"margin:0px;\n"
"}\n"
"\n"
"QMenu::item{\n"
"padding:3px 10px;\n"
"}\n"
"\n"
"QMenu::indicator{\n"
"width:13px;\n"
"height:13px;\n"
"}\n"
"\n"
"QMenu::item:selected,QMenuBar::item:selected{\n"
"color:#DCDCDC;\n"
"border:0px solid #242424;\n"
"background:#646464;\n"
"}\n"
"\n"
"QMenu::separator{\n"
"height:1px;\n"
"background:#242424;\n"
"}\n"
"\n"
"QProgressBar{\n"
"min-height:10px;\n"
"background:#484848;\n"
"border-radius:5px;\n"
"text-align:center;\n"
"border:1px solid #484848;\n"
"}\n"
"\n"
"QProgressBar:chunk{\n"
"border-radius:5px;\n"
"background-color:#"
                        "242424;\n"
"}\n"
"\n"
"QSlider::groove:horizontal{\n"
"background:#484848;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal{\n"
"background:#484848;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal{\n"
"background:#242424;\n"
"height:8px;\n"
"border-radius:4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal{\n"
"width:13px;\n"
"margin-top:-3px;\n"
"margin-bottom:-3px;\n"
"border-radius:6px;\n"
"background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #444444,stop:0.8 #242424);\n"
"}\n"
"\n"
"QSlider::groove:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#484848;\n"
"}\n"
"\n"
"QSlider::add-page:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#484848;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical{\n"
"width:8px;\n"
"border-radius:4px;\n"
"background:#242424;\n"
"}\n"
"\n"
"QSlider::handle:vertical{\n"
"height:14px;\n"
"margin-left:-3px;\n"
"margin-right:-3px;\n"
"border-radius:6px;\n"
"backgrou"
                        "nd:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #444444,stop:0.8 #242424);\n"
"}\n"
"\n"
"QScrollBar:horizontal{\n"
"background:#484848;\n"
"padding:0px;\n"
"border-radius:1px;\n"
"max-height:8px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal{\n"
"background:#525252;\n"
"min-width:50px;\n"
"border-radius:3px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover{\n"
"background:#242424;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:pressed{\n"
"background:#242424;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-page:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar:vertical{\n"
"background:#484848;\n"
"padding:0px;\n"
"border-radius:2px;\n"
"max-width:9px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical{\n"
"background:#525252;\n"
"min-height:50px;\n"
"border-radius:6px;\n"
"}\n"
"\n"
"QScrollBa"
                        "r::handle:vertical:hover{\n"
"background:#242424;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:pressed{\n"
"background:#242424;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-page:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical{\n"
"background:none;\n"
"}\n"
"\n"
"QScrollArea{\n"
"border:0px;\n"
"}\n"
"\n"
"QTreeView,QListView,QTableView,QTabWidget::pane{\n"
"border:1px solid #242424;\n"
"selection-background-color:#646464;\n"
"selection-color:#DCDCDC;\n"
"alternate-background-color:#525252;\n"
"gridline-color:#242424;\n"
"}\n"
"\n"
"QTreeView::branch:closed:has-children{\n"
"margin:4px;\n"
"border-image:url(:/Ticon/psblack/add_right.png);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children{\n"
"margin:4px;\n"
"border-image:url(:/Ticon/psblack/add_bottom.png);\n"
"}\n"
"\n"
"QTreeView,QListView,QTableView,QSplitter::handle,QTreeView::branch{\n"
"background:#444444;\n"
""
                        "}\n"
"\n"
"QTableView::item:selected,QListView::item:selected,QTreeView::item:selected{\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QTableView::item:hover,QListView::item:hover,QTreeView::item:hover{\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QTableView::item,QListView::item,QTreeView::item{\n"
"padding:1px;\n"
"margin:0px;\n"
"}\n"
"\n"
"QHeaderView::section,QTableCornerButton:section{\n"
"padding:3px;\n"
"margin:0px;\n"
"color:#DCDCDC;\n"
"border:1px solid #242424;\n"
"border-left-width:0px;\n"
"border-right-width:1px;\n"
"border-top-width:0px;\n"
"border-bottom-width:1px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"border:1px solid #242424;\n"
"color:#DCDCDC;\n"
"margin:0px;\n"
"border-style: solid;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1"
                        ",stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QTabBar::tab:selected,QTabBar::tab:hover{\n"
"border-style:solid;\n"
"border-color:#00BB9E;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QTabBar::tab:top,QTabBar::tab:bottom{\n"
"padding:3px 8px 3px 8px;\n"
"}\n"
"\n"
"QTabBar::tab:left,QTabBar::tab:right{\n"
"padding:8px 3px 8px 3px;\n"
"}\n"
"\n"
"QTabBar::tab:top:selected,QTabBar::tab:top:hover{\n"
"border-width:2px 0px 0px 0px;\n"
"}\n"
"\n"
"QTabBar::tab:right:selected,QTabBar::tab:right:hover{\n"
"border-width:0px 0px 0px 2px;\n"
"}\n"
"\n"
"QTabBar::tab:bottom:selected,QTabBar::tab:bottom:hover{\n"
"border-width:0px 0px 2px 0px;\n"
"}\n"
"\n"
"QTabBar::tab:left:selected,QTabBar::tab:left:hover{\n"
"border-width:0px 2px 0px 0px;\n"
"}\n"
"\n"
"QTabBar::tab:first:top:selected,QTabBar::tab:first:top:hover,QTabBar::tab:first:bottom:selected,QTabBar::tab:first:bottom:hover{\n"
"border-left-width:1px;\n"
"border-left-color:#242424;\n"
"}\n"
"\n"
"QT"
                        "abBar::tab:first:left:selected,QTabBar::tab:first:left:hover,QTabBar::tab:first:right:selected,QTabBar::tab:first:right:hover{\n"
"border-top-width:1px;\n"
"border-top-color:#242424;\n"
"}\n"
"\n"
"QTabBar::tab:last:top:selected,QTabBar::tab:last:top:hover,QTabBar::tab:last:bottom:selected,QTabBar::tab:last:bottom:hover{\n"
"border-right-width:1px;\n"
"border-right-color:#242424;\n"
"}\n"
"\n"
"QTabBar::tab:last:left:selected,QTabBar::tab:last:left:hover,QTabBar::tab:last:right:selected,QTabBar::tab:last:right:hover{\n"
"border-bottom-width:1px;\n"
"border-bottom-color:#242424;\n"
"}\n"
"\n"
"QStatusBar::item{\n"
"border:0px solid #484848;\n"
"border-radius:3px;\n"
"}\n"
"QToolBox{\n"
"    color: #b1b1b1;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 2px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font"
                        "-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QToolBox::tab,QGroupBox#gboxDevicePanel,QGroupBox#gboxDeviceTitle,QFrame#gboxDevicePanel,QFrame#gboxDeviceTitle{\n"
"padding:1px;\n"
"border-radius:5px;\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QToolTip{\n"
"border:1px solid #DCDCDC;\n"
"padding:2px;\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"opacity: 230;\n"
"}\n"
"\n"
"QToolBox::tab:selected{\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
" border-bottom: 1px solid #14506B;\n"
" border-top: 1px solid #14506B;\n"
"border-left: 1px solid #14506B;\n"
"border-right: 1px solid #14506B;\n"
"}\n"
"\n"
"QPrintPreviewDialog QToolButton{\n"
"border:0px solid #DCDCDC;\n"
"border-radius:0px;\n"
"margin:0px;\n"
"padding:3px;\n"
"background:none;\n"
"}\n"
"\n"
"QColorDialog QPushButt"
                        "on,QFileDialog QPushButton{\n"
"min-width:80px;\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth{\n"
"icon-size:0px;\n"
"min-width:20px;\n"
"image:url(:/Ticon/psblack/calendar_prevmonth.png);\n"
"}\n"
"\n"
"QToolButton#qt_calendar_nextmonth{\n"
"icon-size:0px;\n"
"min-width:20px;\n"
"image:url(:/Ticon/psblack/calendar_nextmonth.png)\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth,QToolButton#qt_calendar_nextmonth,QToolButton#qt_calendar_monthbutton,QToolButton#qt_calendar_yearbutton{\n"
"border:0px solid #DCDCDC;\n"
"border-radius:3px;\n"
"margin:3px 3px 3px 3px;\n"
"padding:3px;\n"
"background:none;\n"
"}\n"
"\n"
"QToolButton#qt_calendar_prevmonth:hover,QToolButton#qt_calendar_nextmonth:hover,QToolButton#qt_calendar_monthbutton:hover,QToolButton#qt_calendar_yearbutton:hover,QToolButton#qt_calendar_prevmonth:pressed,QToolButton#qt_calendar_nextmonth:pressed,QToolButton#qt_calendar_monthbutton:pressed,QToolButton#qt_calendar_yearbutton:pressed{\n"
"border:1px solid #242424;\n"
"}\n"
"\n"
"QCalendarWidget QSpin"
                        "Box#qt_calendar_yearedit{\n"
"margin:2px;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton::menu-indicator{\n"
"image:None;\n"
"}\n"
"\n"
"QCalendarWidget QTableView{\n"
"border-width:0px;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar{\n"
"border:1px solid #242424;\n"
"border-width:1px 1px 0px 1px;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item{\n"
"min-height:20px;\n"
"min-width:10px;\n"
"}\n"
"\n"
"QTableView[model=\"true\"]::item{\n"
"padding:0px;\n"
"margin:0px;\n"
"}\n"
"\n"
"QTableView QLineEdit,QTableView QComboBox,QTableView QSpinBox,QTableView QDoubleSpinBox,QTableView QDateEdit,QTableView QTimeEdit,QTableView QDateTimeEdit{\n"
"border-width:0px;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"QTableView QLineEdit:focus,QTableView QComboBox:focus,QTableView QSpinBox:focus,QTableView QDoubleSpinBox:focus,QTableView QDateEdit:focus,QTableView QTimeEdit:focus,QTableView QDateTimeEdit:focus{\n"
"border-width"
                        ":0px;\n"
"border-radius:0px;\n"
"}\n"
"\n"
"QLineEdit,QTextEdit,QPlainTextEdit,QSpinBox,QDoubleSpinBox,QComboBox,QDateEdit,QTimeEdit,QDateTimeEdit{\n"
"background:#444444;\n"
"}"));
        SurfaceGridSwitch = new QAction(MainWindow);
        SurfaceGridSwitch->setObjectName(QString::fromUtf8("SurfaceGridSwitch"));
        SurfaceGridSwitch->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Ticon/Resources/\347\275\221\346\240\274.png"), QSize(), QIcon::Normal, QIcon::Off);
        SurfaceGridSwitch->setIcon(icon1);
        actiona = new QAction(MainWindow);
        actiona->setObjectName(QString::fromUtf8("actiona"));
        actiona->setIcon(icon1);
        actiona->setMenuRole(QAction::TextHeuristicRole);
        actionb = new QAction(MainWindow);
        actionb->setObjectName(QString::fromUtf8("actionb"));
        actionb->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Ticon/Resources/icon (1).ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionb->setIcon(icon2);
        actionb->setIconVisibleInMenu(true);
        actiondaoch = new QAction(MainWindow);
        actiondaoch->setObjectName(QString::fromUtf8("actiondaoch"));
        actionc = new QAction(MainWindow);
        actionc->setObjectName(QString::fromUtf8("actionc"));
        actionzanchun = new QAction(MainWindow);
        actionzanchun->setObjectName(QString::fromUtf8("actionzanchun"));
        actionzairu = new QAction(MainWindow);
        actionzairu->setObjectName(QString::fromUtf8("actionzairu"));
        actiontritoquad = new QAction(MainWindow);
        actiontritoquad->setObjectName(QString::fromUtf8("actiontritoquad"));
        actiontritotet = new QAction(MainWindow);
        actiontritotet->setObjectName(QString::fromUtf8("actiontritotet"));
        actionMeshSimplification = new QAction(MainWindow);
        actionMeshSimplification->setObjectName(QString::fromUtf8("actionMeshSimplification"));
        actionMeshRemesh = new QAction(MainWindow);
        actionMeshRemesh->setObjectName(QString::fromUtf8("actionMeshRemesh"));
        actionMeshAddNoise = new QAction(MainWindow);
        actionMeshAddNoise->setObjectName(QString::fromUtf8("actionMeshAddNoise"));
        actionMeshSmooth = new QAction(MainWindow);
        actionMeshSmooth->setObjectName(QString::fromUtf8("actionMeshSmooth"));
        actionSubdivision = new QAction(MainWindow);
        actionSubdivision->setObjectName(QString::fromUtf8("actionSubdivision"));
        actionMinimalSurface = new QAction(MainWindow);
        actionMinimalSurface->setObjectName(QString::fromUtf8("actionMinimalSurface"));
        actionLSCM = new QAction(MainWindow);
        actionLSCM->setObjectName(QString::fromUtf8("actionLSCM"));
        actionBFF = new QAction(MainWindow);
        actionBFF->setObjectName(QString::fromUtf8("actionBFF"));
        actionMeshFix = new QAction(MainWindow);
        actionMeshFix->setObjectName(QString::fromUtf8("actionMeshFix"));
        actionCADRemeshing = new QAction(MainWindow);
        actionCADRemeshing->setObjectName(QString::fromUtf8("actionCADRemeshing"));
        actionRevertNormal = new QAction(MainWindow);
        actionRevertNormal->setObjectName(QString::fromUtf8("actionRevertNormal"));
        actionCloseMesh = new QAction(MainWindow);
        actionCloseMesh->setObjectName(QString::fromUtf8("actionCloseMesh"));
        actionTetSimplification = new QAction(MainWindow);
        actionTetSimplification->setObjectName(QString::fromUtf8("actionTetSimplification"));
        actionMotorcycleGraphs = new QAction(MainWindow);
        actionMotorcycleGraphs->setObjectName(QString::fromUtf8("actionMotorcycleGraphs"));
        actionBoolean = new QAction(MainWindow);
        actionBoolean->setObjectName(QString::fromUtf8("actionBoolean"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_11 = new QHBoxLayout(centralwidget);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 3, 0);
        funcTab = new QTabWidget(centralwidget);
        funcTab->setObjectName(QString::fromUtf8("funcTab"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(funcTab->sizePolicy().hasHeightForWidth());
        funcTab->setSizePolicy(sizePolicy1);
        funcTab->setMinimumSize(QSize(280, 0));
        funcTab->setMaximumSize(QSize(300, 16777215));
        funcTab->setSizeIncrement(QSize(0, 0));
        funcTab->setMouseTracking(true);
        funcTab->setToolTipDuration(0);
        funcTab->setAutoFillBackground(false);
        funcTab->setStyleSheet(QString::fromUtf8(""));
        funcTab->setTabPosition(QTabWidget::North);
        funcTab->setTabShape(QTabWidget::Rounded);
        funcTab->setIconSize(QSize(42, 30));
        funcTab->setElideMode(Qt::ElideNone);
        funcTab->setUsesScrollButtons(true);
        funcTab->setDocumentMode(false);
        funcTab->setTabsClosable(false);
        funcTab->setMovable(false);
        funcTab->setTabBarAutoHide(true);
        TriMesh = new QWidget();
        TriMesh->setObjectName(QString::fromUtf8("TriMesh"));
        verticalLayout_7 = new QVBoxLayout(TriMesh);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(TriMesh);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("image: url(:/Ticon/Resources/iGameLogo.png);"));

        verticalLayout_7->addWidget(label);

        tabWidget = new QTabWidget(TriMesh);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setUsesScrollButtons(true);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        verticalLayout_19 = new QVBoxLayout(tab1);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        scrollArea_2 = new QScrollArea(tab1);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 276, 472));
        verticalLayout_18 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(3, 6, 3, 3);
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        verticalLayout_10 = new QVBoxLayout(groupBox_2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(5, 5, 5, 5);
        btnOpenMesh = new QPushButton(groupBox_2);
        btnOpenMesh->setObjectName(QString::fromUtf8("btnOpenMesh"));
        btnOpenMesh->setMinimumSize(QSize(0, 25));
        btnOpenMesh->setMaximumSize(QSize(16777215, 25));
        btnOpenMesh->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Ticon/Resources/icon (4).png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpenMesh->setIcon(icon3);
        btnOpenMesh->setIconSize(QSize(20, 20));

        verticalLayout_10->addWidget(btnOpenMesh);

        btnSaveMesh = new QPushButton(groupBox_2);
        btnSaveMesh->setObjectName(QString::fromUtf8("btnSaveMesh"));
        btnSaveMesh->setMaximumSize(QSize(16777215, 25));
        btnSaveMesh->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Ticon/Resources/icon (5).png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSaveMesh->setIcon(icon4);
        btnSaveMesh->setIconSize(QSize(18, 18));

        verticalLayout_10->addWidget(btnSaveMesh);


        verticalLayout_18->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy3.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy3);
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        btnSurfaceFairing = new QPushButton(groupBox_4);
        btnSurfaceFairing->setObjectName(QString::fromUtf8("btnSurfaceFairing"));

        verticalLayout_2->addWidget(btnSurfaceFairing);

        btnSurfacePara = new QPushButton(groupBox_4);
        btnSurfacePara->setObjectName(QString::fromUtf8("btnSurfacePara"));

        verticalLayout_2->addWidget(btnSurfacePara);

        btnCopyMesh = new QPushButton(groupBox_4);
        btnCopyMesh->setObjectName(QString::fromUtf8("btnCopyMesh"));
        btnCopyMesh->setMaximumSize(QSize(16777215, 25));
        btnCopyMesh->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Ticon/Resources/import1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCopyMesh->setIcon(icon5);
        btnCopyMesh->setIconSize(QSize(15, 15));

        verticalLayout_2->addWidget(btnCopyMesh);

        btnRecoverMesh = new QPushButton(groupBox_4);
        btnRecoverMesh->setObjectName(QString::fromUtf8("btnRecoverMesh"));
        btnRecoverMesh->setMaximumSize(QSize(16777215, 25));
        btnRecoverMesh->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Ticon/Resources/import2.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRecoverMesh->setIcon(icon6);
        btnRecoverMesh->setIconSize(QSize(15, 15));

        verticalLayout_2->addWidget(btnRecoverMesh);


        verticalLayout_18->addWidget(groupBox_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_3);

        scrollArea_2->setWidget(scrollAreaWidgetContents);

        verticalLayout_19->addWidget(scrollArea_2);

        tabWidget->addTab(tab1, icon1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        verticalLayout_21 = new QVBoxLayout(tab2);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        scrollArea_3 = new QScrollArea(tab2);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 276, 472));
        verticalLayout_20 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(3, 3, 3, 3);
        groupBox = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_33 = new QVBoxLayout(groupBox);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        verticalLayout_33->setContentsMargins(5, 5, 5, 5);
        btnOpenHedra = new QPushButton(groupBox);
        btnOpenHedra->setObjectName(QString::fromUtf8("btnOpenHedra"));
        btnOpenHedra->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnOpenHedra->sizePolicy().hasHeightForWidth());
        btnOpenHedra->setSizePolicy(sizePolicy4);
        btnOpenHedra->setMinimumSize(QSize(0, 25));
        btnOpenHedra->setFont(font);
        btnOpenHedra->setIcon(icon3);
        btnOpenHedra->setIconSize(QSize(20, 20));

        verticalLayout_33->addWidget(btnOpenHedra);

        btnSaveHedra = new QPushButton(groupBox);
        btnSaveHedra->setObjectName(QString::fromUtf8("btnSaveHedra"));
        sizePolicy4.setHeightForWidth(btnSaveHedra->sizePolicy().hasHeightForWidth());
        btnSaveHedra->setSizePolicy(sizePolicy4);
        btnSaveHedra->setMinimumSize(QSize(0, 25));
        btnSaveHedra->setFont(font);
        btnSaveHedra->setFocusPolicy(Qt::StrongFocus);
        btnSaveHedra->setIcon(icon4);
        btnSaveHedra->setIconSize(QSize(18, 18));

        verticalLayout_33->addWidget(btnSaveHedra);


        verticalLayout_20->addWidget(groupBox);

        verticalSpacer_9 = new QSpacerItem(20, 500, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_9);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_21->addWidget(scrollArea_3);

        tabWidget->addTab(tab2, icon2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QString::fromUtf8("tab3"));
        verticalLayout_23 = new QVBoxLayout(tab3);
        verticalLayout_23->setSpacing(0);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(0, 0, 0, 0);
        scrollArea_4 = new QScrollArea(tab3);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 267, 593));
        verticalLayout_22 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        groupBox_15 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        verticalLayout_27 = new QVBoxLayout(groupBox_15);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        verticalLayout_27->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnLastMesh = new QPushButton(groupBox_15);
        btnLastMesh->setObjectName(QString::fromUtf8("btnLastMesh"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Ticon/Resources/arrow_click_cursor_pointer_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLastMesh->setIcon(icon7);
        btnLastMesh->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(btnLastMesh);

        btnNextMesh = new QPushButton(groupBox_15);
        btnNextMesh->setObjectName(QString::fromUtf8("btnNextMesh"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Ticon/Resources/arrow_click_cursor_pointer_icon (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNextMesh->setIcon(icon8);
        btnNextMesh->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(btnNextMesh);


        verticalLayout_27->addLayout(horizontalLayout_3);


        verticalLayout_22->addWidget(groupBox_15);

        groupBox_6 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_8 = new QVBoxLayout(groupBox_6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnInfoClear = new QPushButton(groupBox_6);
        btnInfoClear->setObjectName(QString::fromUtf8("btnInfoClear"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Ticon/Resources/\346\270\205\347\251\272.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnInfoClear->setIcon(icon9);

        horizontalLayout_4->addWidget(btnInfoClear);

        btnInfoCopy = new QPushButton(groupBox_6);
        btnInfoCopy->setObjectName(QString::fromUtf8("btnInfoCopy"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Ticon/Resources/icon (2).png"), QSize(), QIcon::Normal, QIcon::Off);
        btnInfoCopy->setIcon(icon10);
        btnInfoCopy->setIconSize(QSize(18, 18));

        horizontalLayout_4->addWidget(btnInfoCopy);


        verticalLayout_8->addLayout(horizontalLayout_4);


        verticalLayout_22->addWidget(groupBox_6);

        groupBox_13 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        horizontalLayout = new QHBoxLayout(groupBox_13);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(groupBox_13);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_13 = new QVBoxLayout(groupBox_5);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        rtnModelView = new QRadioButton(groupBox_5);
        rtnModelView->setObjectName(QString::fromUtf8("rtnModelView"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Ticon/Resources/6610 - View.png"), QSize(), QIcon::Normal, QIcon::Off);
        rtnModelView->setIcon(icon11);
        rtnModelView->setChecked(false);

        verticalLayout_13->addWidget(rtnModelView);

        rtnModelEdit = new QRadioButton(groupBox_5);
        rtnModelEdit->setObjectName(QString::fromUtf8("rtnModelEdit"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Ticon/Resources/Setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        rtnModelEdit->setIcon(icon12);
        rtnModelEdit->setChecked(true);

        verticalLayout_13->addWidget(rtnModelEdit);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_13->addItem(verticalSpacer_4);

        rtnPickItem = new QRadioButton(groupBox_5);
        rtnPickItem->setObjectName(QString::fromUtf8("rtnPickItem"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Ticon/Resources/arrow_click_cursor_pointer_icon .png"), QSize(), QIcon::Normal, QIcon::Off);
        rtnPickItem->setIcon(icon13);

        verticalLayout_13->addWidget(rtnPickItem);

        verticalSpacer_5 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_5);

        rtnModelCut = new QRadioButton(groupBox_5);
        rtnModelCut->setObjectName(QString::fromUtf8("rtnModelCut"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Ticon/Resources/knife_cutter_cut_cutlery_cutting_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        rtnModelCut->setIcon(icon14);
        rtnModelCut->setIconSize(QSize(14, 14));

        verticalLayout_13->addWidget(rtnModelCut);

        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_13->addItem(verticalSpacer_8);


        horizontalLayout->addWidget(groupBox_5);

        groupBox_11 = new QGroupBox(groupBox_13);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        verticalLayout_9 = new QVBoxLayout(groupBox_11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(5, 5, 5, 5);
        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_10);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_8 = new QGroupBox(groupBox_11);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_3 = new QVBoxLayout(groupBox_8);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        rtnPickPoint = new QRadioButton(groupBox_8);
        rtnPickPoint->setObjectName(QString::fromUtf8("rtnPickPoint"));
        rtnPickPoint->setChecked(true);

        horizontalLayout_13->addWidget(rtnPickPoint);

        rtnPickEdge = new QRadioButton(groupBox_8);
        rtnPickEdge->setObjectName(QString::fromUtf8("rtnPickEdge"));

        horizontalLayout_13->addWidget(rtnPickEdge);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        rtnPickFace = new QRadioButton(groupBox_8);
        rtnPickFace->setObjectName(QString::fromUtf8("rtnPickFace"));

        horizontalLayout_14->addWidget(rtnPickFace);

        rtnPickCell = new QRadioButton(groupBox_8);
        rtnPickCell->setObjectName(QString::fromUtf8("rtnPickCell"));

        horizontalLayout_14->addWidget(rtnPickCell);


        verticalLayout_3->addLayout(horizontalLayout_14);


        horizontalLayout_7->addWidget(groupBox_8);


        verticalLayout_12->addLayout(horizontalLayout_7);

        btnPickRemoveAll = new QPushButton(groupBox_11);
        btnPickRemoveAll->setObjectName(QString::fromUtf8("btnPickRemoveAll"));

        verticalLayout_12->addWidget(btnPickRemoveAll);


        verticalLayout_9->addLayout(verticalLayout_12);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_9->addItem(verticalSpacer_6);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        btnToCut = new QPushButton(groupBox_11);
        btnToCut->setObjectName(QString::fromUtf8("btnToCut"));

        verticalLayout_14->addWidget(btnToCut);

        btnRemoveLine = new QPushButton(groupBox_11);
        btnRemoveLine->setObjectName(QString::fromUtf8("btnRemoveLine"));

        verticalLayout_14->addWidget(btnRemoveLine);


        verticalLayout_9->addLayout(verticalLayout_14);


        horizontalLayout->addWidget(groupBox_11);


        verticalLayout_22->addWidget(groupBox_13);

        groupBox_10 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout_15 = new QVBoxLayout(groupBox_10);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(5, 5, 5, 5);
        ckbCutPlane = new QCheckBox(groupBox_10);
        ckbCutPlane->setObjectName(QString::fromUtf8("ckbCutPlane"));
        ckbCutPlane->setChecked(false);

        verticalLayout_15->addWidget(ckbCutPlane);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_2 = new QLabel(groupBox_10);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_12->addWidget(label_2);

        cutPlaneX = new QSlider(groupBox_10);
        cutPlaneX->setObjectName(QString::fromUtf8("cutPlaneX"));
        cutPlaneX->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(cutPlaneX);


        verticalLayout_16->addLayout(horizontalLayout_12);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_3 = new QLabel(groupBox_10);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_15->addWidget(label_3);

        cutPlaneY = new QSlider(groupBox_10);
        cutPlaneY->setObjectName(QString::fromUtf8("cutPlaneY"));
        cutPlaneY->setOrientation(Qt::Horizontal);

        horizontalLayout_15->addWidget(cutPlaneY);


        verticalLayout_16->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_4 = new QLabel(groupBox_10);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_16->addWidget(label_4);

        cutPlaneZ = new QSlider(groupBox_10);
        cutPlaneZ->setObjectName(QString::fromUtf8("cutPlaneZ"));
        cutPlaneZ->setOrientation(Qt::Horizontal);

        horizontalLayout_16->addWidget(cutPlaneZ);


        verticalLayout_16->addLayout(horizontalLayout_16);


        verticalLayout_15->addLayout(verticalLayout_16);


        verticalLayout_22->addWidget(groupBox_10);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_23->addWidget(scrollArea_4);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Ticon/Resources/Configuration.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab3, icon15, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_36 = new QVBoxLayout(tab);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        groupBox_16 = new QGroupBox(tab);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        verticalLayout_28 = new QVBoxLayout(groupBox_16);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        verticalLayout_28->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(groupBox_16);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        triMeshComboBox = new QComboBox(groupBox_16);
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->addItem(QString());
        triMeshComboBox->setObjectName(QString::fromUtf8("triMeshComboBox"));

        horizontalLayout_2->addWidget(triMeshComboBox);


        verticalLayout_28->addLayout(horizontalLayout_2);

        labelTriMetric = new QLabel(groupBox_16);
        labelTriMetric->setObjectName(QString::fromUtf8("labelTriMetric"));

        verticalLayout_28->addWidget(labelTriMetric);


        verticalLayout_36->addWidget(groupBox_16);

        groupBox_19 = new QGroupBox(tab);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        verticalLayout_32 = new QVBoxLayout(groupBox_19);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        verticalLayout_32->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(groupBox_19);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        quadMeshComboBox = new QComboBox(groupBox_19);
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->addItem(QString());
        quadMeshComboBox->setObjectName(QString::fromUtf8("quadMeshComboBox"));

        horizontalLayout_9->addWidget(quadMeshComboBox);


        verticalLayout_32->addLayout(horizontalLayout_9);

        labelQuadMetric = new QLabel(groupBox_19);
        labelQuadMetric->setObjectName(QString::fromUtf8("labelQuadMetric"));

        verticalLayout_32->addWidget(labelQuadMetric);


        verticalLayout_36->addWidget(groupBox_19);

        groupBox_18 = new QGroupBox(tab);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        verticalLayout_31 = new QVBoxLayout(groupBox_18);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        verticalLayout_31->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_18);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        tetMeshComboBox = new QComboBox(groupBox_18);
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->addItem(QString());
        tetMeshComboBox->setObjectName(QString::fromUtf8("tetMeshComboBox"));

        horizontalLayout_8->addWidget(tetMeshComboBox);


        verticalLayout_31->addLayout(horizontalLayout_8);

        labelTetMetric = new QLabel(groupBox_18);
        labelTetMetric->setObjectName(QString::fromUtf8("labelTetMetric"));

        verticalLayout_31->addWidget(labelTetMetric);


        verticalLayout_36->addWidget(groupBox_18);

        groupBox_17 = new QGroupBox(tab);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        verticalLayout_30 = new QVBoxLayout(groupBox_17);
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        verticalLayout_30->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(groupBox_17);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        hexMeshComboBox = new QComboBox(groupBox_17);
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->addItem(QString());
        hexMeshComboBox->setObjectName(QString::fromUtf8("hexMeshComboBox"));

        horizontalLayout_5->addWidget(hexMeshComboBox);


        verticalLayout_30->addLayout(horizontalLayout_5);

        labelHexMetric = new QLabel(groupBox_17);
        labelHexMetric->setObjectName(QString::fromUtf8("labelHexMetric"));

        verticalLayout_30->addWidget(labelHexMetric);


        verticalLayout_36->addWidget(groupBox_17);

        verticalSpacer_2 = new QSpacerItem(20, 276, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_36->addItem(verticalSpacer_2);

        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Ticon/Resources/icon (8).png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon16, QString());

        verticalLayout_7->addWidget(tabWidget);

        modelListWidget = new QTreeWidget(TriMesh);
        modelListWidget->headerItem()->setText(0, QString());
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        modelListWidget->setHeaderItem(__qtreewidgetitem);
        modelListWidget->setObjectName(QString::fromUtf8("modelListWidget"));
        sizePolicy.setHeightForWidth(modelListWidget->sizePolicy().hasHeightForWidth());
        modelListWidget->setSizePolicy(sizePolicy);
        modelListWidget->setFrameShape(QFrame::StyledPanel);
        modelListWidget->setLineWidth(1);
        modelListWidget->setAutoScrollMargin(16);
        modelListWidget->setProperty("showDropIndicator", QVariant(true));
        modelListWidget->setAutoExpandDelay(1);
        modelListWidget->setColumnCount(2);
        modelListWidget->header()->setVisible(false);
        modelListWidget->header()->setCascadingSectionResizes(false);
        modelListWidget->header()->setMinimumSectionSize(24);
        modelListWidget->header()->setDefaultSectionSize(140);
        modelListWidget->header()->setHighlightSections(false);
        modelListWidget->header()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout_7->addWidget(modelListWidget);

        verticalLayout_7->setStretch(0, 2);
        verticalLayout_7->setStretch(1, 8);
        verticalLayout_7->setStretch(2, 3);
        funcTab->addTab(TriMesh, QString());

        horizontalLayout_11->addWidget(funcTab);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_17->setContentsMargins(-1, 0, -1, -1);
        viewBox = new QWidget(centralwidget);
        viewBox->setObjectName(QString::fromUtf8("viewBox"));
        sizePolicy2.setHeightForWidth(viewBox->sizePolicy().hasHeightForWidth());
        viewBox->setSizePolicy(sizePolicy2);
        verticalLayout_25 = new QVBoxLayout(viewBox);
        verticalLayout_25->setSpacing(3);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, -1, 3, -1);
        MetricChartWidget = new MetricChart(viewBox);
        MetricChartWidget->setObjectName(QString::fromUtf8("MetricChartWidget"));
        sizePolicy1.setHeightForWidth(MetricChartWidget->sizePolicy().hasHeightForWidth());
        MetricChartWidget->setSizePolicy(sizePolicy1);
        MetricChartWidget->setMinimumSize(QSize(215, 500));
        verticalLayout_37 = new QVBoxLayout(MetricChartWidget);
        verticalLayout_37->setSpacing(3);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        verticalLayout_37->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_10->addWidget(MetricChartWidget);

        openGLWidget = new ModelDraw(viewBox);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        sizePolicy2.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy2);

        horizontalLayout_10->addWidget(openGLWidget);


        verticalLayout_25->addLayout(horizontalLayout_10);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        outputWidget_2 = new QDockWidget(viewBox);
        outputWidget_2->setObjectName(QString::fromUtf8("outputWidget_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(4);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(outputWidget_2->sizePolicy().hasHeightForWidth());
        outputWidget_2->setSizePolicy(sizePolicy5);
        outputWidget_2->setMinimumSize(QSize(38, 61));
        QFont font1;
        font1.setStyleStrategy(QFont::PreferAntialias);
        outputWidget_2->setFont(font1);
        outputWidget_2->setFloating(false);
        outputWidget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);
        outputWidget_2->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_29 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        showInformation = new QLabel(dockWidgetContents_2);
        showInformation->setObjectName(QString::fromUtf8("showInformation"));
        QFont font2;
        font2.setPointSize(10);
        showInformation->setFont(font2);
        showInformation->setLayoutDirection(Qt::LeftToRight);
        showInformation->setAutoFillBackground(false);
        showInformation->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255\357\274\2141);"));
        showInformation->setFrameShape(QFrame::NoFrame);
        showInformation->setFrameShadow(QFrame::Plain);
        showInformation->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_29->addWidget(showInformation);

        outputWidget_2->setWidget(dockWidgetContents_2);

        horizontalLayout_18->addWidget(outputWidget_2);

        outputWidget = new QDockWidget(viewBox);
        outputWidget->setObjectName(QString::fromUtf8("outputWidget"));
        sizePolicy5.setHeightForWidth(outputWidget->sizePolicy().hasHeightForWidth());
        outputWidget->setSizePolicy(sizePolicy5);
        outputWidget->setMinimumSize(QSize(105, 126));
        outputWidget->setFont(font1);
        outputWidget->setFloating(false);
        outputWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        outputWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_6 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(3, 3, 3, 3);
        info = new PrintInfo(dockWidgetContents);
        info->setObjectName(QString::fromUtf8("info"));
        sizePolicy2.setHeightForWidth(info->sizePolicy().hasHeightForWidth());
        info->setSizePolicy(sizePolicy2);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Microsoft JhengHei"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        info->setFont(font3);
        info->setOpenExternalLinks(false);

        horizontalLayout_6->addWidget(info);

        outputWidget->setWidget(dockWidgetContents);

        horizontalLayout_18->addWidget(outputWidget);

        horizontalLayout_18->setStretch(0, 2);
        horizontalLayout_18->setStretch(1, 8);

        verticalLayout_25->addLayout(horizontalLayout_18);

        verticalLayout_25->setStretch(0, 10);
        verticalLayout_25->setStretch(1, 3);

        horizontalLayout_17->addWidget(viewBox);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ckbSurfaceGrid = new QPushButton(centralwidget);
        ckbSurfaceGrid->setObjectName(QString::fromUtf8("ckbSurfaceGrid"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(ckbSurfaceGrid->sizePolicy().hasHeightForWidth());
        ckbSurfaceGrid->setSizePolicy(sizePolicy6);
        ckbSurfaceGrid->setMinimumSize(QSize(30, 30));
        ckbSurfaceGrid->setMaximumSize(QSize(30, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        ckbSurfaceGrid->setFont(font4);
        ckbSurfaceGrid->setLayoutDirection(Qt::LeftToRight);
        ckbSurfaceGrid->setAutoFillBackground(false);
        ckbSurfaceGrid->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/Ticon/Resources/\347\275\221\346\240\274.png);\n"
"background-color: #323232;   \n"
"}\n"
"QPushButton:checked{\n"
"background-color:#6b6b6b;;\n"
"}\n"
"QPushButton{\n"
"min-height:18px;\n"
"}"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Ticon/Resources/mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        ckbSurfaceGrid->setIcon(icon17);
        ckbSurfaceGrid->setIconSize(QSize(25, 25));
        ckbSurfaceGrid->setCheckable(true);
        ckbSurfaceGrid->setChecked(true);

        verticalLayout_4->addWidget(ckbSurfaceGrid);

        ckbCoordCircle = new QPushButton(centralwidget);
        ckbCoordCircle->setObjectName(QString::fromUtf8("ckbCoordCircle"));
        ckbCoordCircle->setEnabled(true);
        sizePolicy6.setHeightForWidth(ckbCoordCircle->sizePolicy().hasHeightForWidth());
        ckbCoordCircle->setSizePolicy(sizePolicy6);
        ckbCoordCircle->setMinimumSize(QSize(30, 30));
        ckbCoordCircle->setMaximumSize(QSize(30, 30));
        ckbCoordCircle->setFont(font4);
        ckbCoordCircle->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/Ticon/Resources/Move.png);\n"
"background-color: #323232;\n"
"   \n"
"}\n"
"QPushButton:checked{\n"
"background-color:#6b6b6b;\n"
"}\n"
"QPushButton{\n"
"min-height:18px;\n"
"}"));
        ckbCoordCircle->setIconSize(QSize(25, 25));
        ckbCoordCircle->setCheckable(true);
        ckbCoordCircle->setChecked(false);

        verticalLayout_4->addWidget(ckbCoordCircle);

        ckbFaceCull = new QPushButton(centralwidget);
        ckbFaceCull->setObjectName(QString::fromUtf8("ckbFaceCull"));
        sizePolicy6.setHeightForWidth(ckbFaceCull->sizePolicy().hasHeightForWidth());
        ckbFaceCull->setSizePolicy(sizePolicy6);
        ckbFaceCull->setMinimumSize(QSize(30, 30));
        ckbFaceCull->setMaximumSize(QSize(30, 30));
        ckbFaceCull->setFont(font4);
        ckbFaceCull->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/Ticon/Resources/6610 - View.png);\n"
"background-color: #323232;\n"
"}\n"
"QPushButton:checked{\n"
"background-color:#6b6b6b;\n"
"}\n"
"QPushButton{\n"
"min-height:18px;\n"
"}\n"
""));
        ckbFaceCull->setIconSize(QSize(25, 25));
        ckbFaceCull->setCheckable(true);

        verticalLayout_4->addWidget(ckbFaceCull);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(199, 199, 199);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        viewpoints = new QPushButton(centralwidget);
        viewpoints->setObjectName(QString::fromUtf8("viewpoints"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(viewpoints->sizePolicy().hasHeightForWidth());
        viewpoints->setSizePolicy(sizePolicy7);
        viewpoints->setMinimumSize(QSize(30, 25));
        viewpoints->setMaximumSize(QSize(30, 30));
        viewpoints->setStyleSheet(QString::fromUtf8(""));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/Ticon/Resources/point.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewpoints->setIcon(icon18);
        viewpoints->setIconSize(QSize(27, 27));
        viewpoints->setCheckable(false);
        viewpoints->setChecked(false);

        verticalLayout_4->addWidget(viewpoints);

        viewlines = new QPushButton(centralwidget);
        viewlines->setObjectName(QString::fromUtf8("viewlines"));
        sizePolicy7.setHeightForWidth(viewlines->sizePolicy().hasHeightForWidth());
        viewlines->setSizePolicy(sizePolicy7);
        viewlines->setMinimumSize(QSize(30, 25));
        viewlines->setMaximumSize(QSize(30, 30));
        viewlines->setStyleSheet(QString::fromUtf8(""));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/Ticon/Resources/3Dmesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewlines->setIcon(icon19);
        viewlines->setIconSize(QSize(27, 27));

        verticalLayout_4->addWidget(viewlines);

        viewfill = new QPushButton(centralwidget);
        viewfill->setObjectName(QString::fromUtf8("viewfill"));
        sizePolicy6.setHeightForWidth(viewfill->sizePolicy().hasHeightForWidth());
        viewfill->setSizePolicy(sizePolicy6);
        viewfill->setMinimumSize(QSize(30, 25));
        viewfill->setMaximumSize(QSize(30, 30));
        viewfill->setStyleSheet(QString::fromUtf8(""));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/Ticon/Resources/facefill.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewfill->setIcon(icon20);
        viewfill->setIconSize(QSize(27, 27));

        verticalLayout_4->addWidget(viewfill);

        viewflatfill = new QPushButton(centralwidget);
        viewflatfill->setObjectName(QString::fromUtf8("viewflatfill"));
        sizePolicy6.setHeightForWidth(viewflatfill->sizePolicy().hasHeightForWidth());
        viewflatfill->setSizePolicy(sizePolicy6);
        viewflatfill->setMinimumSize(QSize(30, 25));
        viewflatfill->setMaximumSize(QSize(30, 30));
        viewflatfill->setStyleSheet(QString::fromUtf8(""));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/Ticon/Resources/icon (12).png"), QSize(), QIcon::Normal, QIcon::Off);
        viewflatfill->setIcon(icon21);
        viewflatfill->setIconSize(QSize(24, 24));

        verticalLayout_4->addWidget(viewflatfill);

        viewlight = new QPushButton(centralwidget);
        viewlight->setObjectName(QString::fromUtf8("viewlight"));
        sizePolicy6.setHeightForWidth(viewlight->sizePolicy().hasHeightForWidth());
        viewlight->setSizePolicy(sizePolicy6);
        viewlight->setMinimumSize(QSize(30, 25));
        viewlight->setMaximumSize(QSize(30, 30));
        viewlight->setStyleSheet(QString::fromUtf8(""));
        viewlight->setIcon(icon18);
        viewlight->setIconSize(QSize(27, 27));

        verticalLayout_4->addWidget(viewlight);

        viewnormal = new QPushButton(centralwidget);
        viewnormal->setObjectName(QString::fromUtf8("viewnormal"));
        sizePolicy6.setHeightForWidth(viewnormal->sizePolicy().hasHeightForWidth());
        viewnormal->setSizePolicy(sizePolicy6);
        viewnormal->setMinimumSize(QSize(30, 25));
        viewnormal->setMaximumSize(QSize(30, 30));
        viewnormal->setStyleSheet(QString::fromUtf8(""));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/Ticon/Resources/colorPoint.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewnormal->setIcon(icon22);
        viewnormal->setIconSize(QSize(30, 30));

        verticalLayout_4->addWidget(viewnormal);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setStyleSheet(QString::fromUtf8("background-color: rgb(199, 199, 199);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        viewReset = new QPushButton(centralwidget);
        viewReset->setObjectName(QString::fromUtf8("viewReset"));
        sizePolicy6.setHeightForWidth(viewReset->sizePolicy().hasHeightForWidth());
        viewReset->setSizePolicy(sizePolicy6);
        viewReset->setMinimumSize(QSize(30, 25));
        viewReset->setMaximumSize(QSize(30, 30));
        viewReset->setStyleSheet(QString::fromUtf8(""));
        viewReset->setIcon(icon16);
        viewReset->setIconSize(QSize(25, 25));

        verticalLayout_4->addWidget(viewReset);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(199, 199, 199);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        btnInformationClear = new QPushButton(centralwidget);
        btnInformationClear->setObjectName(QString::fromUtf8("btnInformationClear"));
        sizePolicy6.setHeightForWidth(btnInformationClear->sizePolicy().hasHeightForWidth());
        btnInformationClear->setSizePolicy(sizePolicy6);
        btnInformationClear->setMinimumSize(QSize(30, 25));
        btnInformationClear->setMaximumSize(QSize(30, 30));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/Ticon/Resources/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnInformationClear->setIcon(icon23);
        btnInformationClear->setIconSize(QSize(24, 24));

        verticalLayout_4->addWidget(btnInformationClear);

        btnLastMesh1 = new QPushButton(centralwidget);
        btnLastMesh1->setObjectName(QString::fromUtf8("btnLastMesh1"));
        sizePolicy6.setHeightForWidth(btnLastMesh1->sizePolicy().hasHeightForWidth());
        btnLastMesh1->setSizePolicy(sizePolicy6);
        btnLastMesh1->setMinimumSize(QSize(30, 25));
        btnLastMesh1->setMaximumSize(QSize(30, 30));
        btnLastMesh1->setFocusPolicy(Qt::NoFocus);
        btnLastMesh1->setStyleSheet(QString::fromUtf8(""));
        btnLastMesh1->setIcon(icon7);
        btnLastMesh1->setIconSize(QSize(40, 40));

        verticalLayout_4->addWidget(btnLastMesh1);

        btnNextMesh1 = new QPushButton(centralwidget);
        btnNextMesh1->setObjectName(QString::fromUtf8("btnNextMesh1"));
        sizePolicy6.setHeightForWidth(btnNextMesh1->sizePolicy().hasHeightForWidth());
        btnNextMesh1->setSizePolicy(sizePolicy6);
        btnNextMesh1->setMinimumSize(QSize(30, 25));
        btnNextMesh1->setMaximumSize(QSize(30, 30));
        btnNextMesh1->setStyleSheet(QString::fromUtf8(""));
        btnNextMesh1->setIcon(icon8);
        btnNextMesh1->setIconSize(QSize(40, 40));

        verticalLayout_4->addWidget(btnNextMesh1);

        viewclear = new QPushButton(centralwidget);
        viewclear->setObjectName(QString::fromUtf8("viewclear"));
        sizePolicy6.setHeightForWidth(viewclear->sizePolicy().hasHeightForWidth());
        viewclear->setSizePolicy(sizePolicy6);
        viewclear->setMinimumSize(QSize(30, 25));
        viewclear->setMaximumSize(QSize(30, 30));
        viewclear->setStyleSheet(QString::fromUtf8(""));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/Ticon/Resources/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        viewclear->setIcon(icon24);
        viewclear->setIconSize(QSize(27, 27));

        verticalLayout_4->addWidget(viewclear);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_17->addLayout(verticalLayout_4);


        horizontalLayout_11->addLayout(horizontalLayout_17);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1213, 25));
        MainWindow->setMenuBar(menuBar);
#if QT_CONFIG(shortcut)
        label->setBuddy(label);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindow);

        funcTab->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        SurfaceGridSwitch->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\345\274\200\345\205\263", nullptr));
#if QT_CONFIG(tooltip)
        SurfaceGridSwitch->setToolTip(QCoreApplication::translate("MainWindow", "\350\241\250\351\235\242\347\275\221\346\240\274\345\274\200\345\205\263", nullptr));
#endif // QT_CONFIG(tooltip)
        actiona->setText(QCoreApplication::translate("MainWindow", "\350\241\250\351\235\242\347\275\221\346\240\274", nullptr));
        actionb->setText(QCoreApplication::translate("MainWindow", "\344\275\223\347\275\221\346\240\274", nullptr));
        actiondaoch->setText(QCoreApplication::translate("MainWindow", "\350\241\250\351\235\242\347\275\221\346\240\274", nullptr));
        actionc->setText(QCoreApplication::translate("MainWindow", "\344\275\223\347\275\221\346\240\274", nullptr));
        actionzanchun->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\255\230\345\275\223\345\211\215\347\275\221\346\240\274", nullptr));
        actionzairu->setText(QCoreApplication::translate("MainWindow", "\350\275\275\345\205\245\346\232\202\345\255\230\347\275\221\346\240\274", nullptr));
        actiontritoquad->setText(QCoreApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242\350\275\254\345\233\233\350\276\271\345\275\242", nullptr));
        actiontritotet->setText(QCoreApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242\350\275\254\345\233\233\351\235\242\344\275\223", nullptr));
        actionMeshSimplification->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\347\256\200\345\214\226", nullptr));
        actionMeshRemesh->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\347\275\221\346\240\274\345\214\226", nullptr));
        actionMeshAddNoise->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\345\212\240\345\231\252", nullptr));
        actionMeshSmooth->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\345\205\211\351\241\272", nullptr));
        actionSubdivision->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\347\273\206\345\210\206", nullptr));
        actionMinimalSurface->setText(QCoreApplication::translate("MainWindow", "\346\236\201\345\260\217\346\233\262\351\235\242\345\214\226", nullptr));
        actionLSCM->setText(QCoreApplication::translate("MainWindow", "LSCM\345\217\202\346\225\260\345\214\226", nullptr));
        actionBFF->setText(QCoreApplication::translate("MainWindow", "BFF\345\217\202\346\225\260\345\214\226", nullptr));
        actionMeshFix->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\344\277\256\345\244\215", nullptr));
        actionCADRemeshing->setText(QCoreApplication::translate("MainWindow", "CAD\351\207\215\346\226\260\347\275\221\346\240\274\345\214\226", nullptr));
        actionRevertNormal->setText(QCoreApplication::translate("MainWindow", "\347\277\273\350\275\254\346\263\225\345\220\221", nullptr));
        actionCloseMesh->setText(QCoreApplication::translate("MainWindow", "\351\227\255\345\220\210\347\275\221\346\240\274", nullptr));
        actionTetSimplification->setText(QCoreApplication::translate("MainWindow", "\344\275\223\347\275\221\346\240\274\347\256\200\345\214\226", nullptr));
        actionMotorcycleGraphs->setText(QCoreApplication::translate("MainWindow", "\345\233\233\350\276\271\345\275\242\351\235\242\347\211\207\345\210\222\345\210\206", nullptr));
        actionBoolean->setText(QCoreApplication::translate("MainWindow", "\345\233\233\350\276\271\345\275\242\345\270\203\345\260\224\350\277\220\347\256\227", nullptr));
        label->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        btnOpenMesh->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\350\241\250\351\235\242\347\275\221\346\240\274", nullptr));
        btnSaveMesh->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\350\241\250\351\235\242\347\275\221\346\240\274", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Mesh", nullptr));
        btnSurfaceFairing->setText(QCoreApplication::translate("MainWindow", "\346\233\262\351\235\242\345\205\211\351\241\272", nullptr));
        btnSurfacePara->setText(QCoreApplication::translate("MainWindow", "\346\233\262\351\235\242\345\217\202\346\225\260\345\214\226", nullptr));
        btnCopyMesh->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\255\230\345\275\223\345\211\215\347\275\221\346\240\274", nullptr));
        btnRecoverMesh->setText(QCoreApplication::translate("MainWindow", "\350\275\275\345\205\245\346\232\202\345\255\230\347\275\221\346\240\274", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "\351\235\242\347\273\223\346\236\204", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        btnOpenHedra->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\344\275\223\347\275\221\346\240\274", nullptr));
        btnSaveHedra->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\344\275\223\347\275\221\346\240\274", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "\344\275\223\347\273\223\346\236\204", nullptr));
        groupBox_15->setTitle(QCoreApplication::translate("MainWindow", "Mesh Choose", nullptr));
        btnLastMesh->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\347\275\221\346\240\274", nullptr));
        btnNextMesh->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\347\275\221\346\240\274", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Information", nullptr));
        btnInfoClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnInfoCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        groupBox_13->setTitle(QString());
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Edit Mode", nullptr));
        rtnModelView->setText(QCoreApplication::translate("MainWindow", "\350\247\202\345\257\237\346\250\241\345\274\217", nullptr));
        rtnModelEdit->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\346\250\241\345\274\217", nullptr));
        rtnPickItem->setText(QCoreApplication::translate("MainWindow", "\347\202\271\351\200\211\346\250\241\345\274\217", nullptr));
        rtnModelCut->setText(QCoreApplication::translate("MainWindow", "\345\210\207\345\211\262\346\250\241\345\274\217", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "PickItem", nullptr));
        rtnPickPoint->setText(QCoreApplication::translate("MainWindow", "\347\202\271", nullptr));
        rtnPickEdge->setText(QCoreApplication::translate("MainWindow", "\347\272\277", nullptr));
        rtnPickFace->setText(QCoreApplication::translate("MainWindow", "\351\235\242", nullptr));
        rtnPickCell->setText(QCoreApplication::translate("MainWindow", "\344\275\223", nullptr));
        btnPickRemoveAll->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\211\200\346\234\211\347\202\271\351\200\211", nullptr));
        btnToCut->setText(QCoreApplication::translate("MainWindow", "\345\210\207\345\211\262", nullptr));
        btnRemoveLine->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\345\210\207\345\211\262\347\272\277", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "\345\210\207\347\211\207", nullptr));
        ckbCutPlane->setText(QCoreApplication::translate("MainWindow", "\345\210\207\347\211\207\346\250\241\345\274\217", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234", nullptr));
        groupBox_16->setTitle(QCoreApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242\347\275\221\346\240\274\350\264\250\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\264\250\351\207\217\346\214\207\346\240\207", nullptr));
        triMeshComboBox->setItemText(0, QString());
        triMeshComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\351\235\242\347\247\257", nullptr));
        triMeshComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\345\206\205\350\247\222", nullptr));
        triMeshComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\206\205\350\247\222", nullptr));
        triMeshComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "\351\233\205\345\205\213\346\257\224", nullptr));
        triMeshComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "\347\272\265\346\250\252\346\257\224", nullptr));
        triMeshComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "\351\225\277\345\256\275\346\257\224", nullptr));

        triMeshComboBox->setCurrentText(QString());
        labelTriMetric->setText(QString());
        groupBox_19->setTitle(QCoreApplication::translate("MainWindow", "\345\233\233\350\276\271\345\275\242\347\275\221\346\240\274\350\264\250\351\207\217", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\350\264\250\351\207\217\346\214\207\346\240\207", nullptr));
        quadMeshComboBox->setItemText(0, QString());
        quadMeshComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\351\235\242\347\247\257", nullptr));
        quadMeshComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\345\206\205\350\247\222", nullptr));
        quadMeshComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\206\205\350\247\222", nullptr));
        quadMeshComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "\351\233\205\345\205\213\346\257\224", nullptr));
        quadMeshComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "\347\272\265\346\250\252\346\257\224", nullptr));
        quadMeshComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "\351\225\277\345\256\275\346\257\224", nullptr));
        quadMeshComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "\347\277\230\346\233\262", nullptr));
        quadMeshComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "\351\224\245\345\272\246", nullptr));
        quadMeshComboBox->setItemText(9, QCoreApplication::translate("MainWindow", "\346\255\252\346\226\234\345\272\246", nullptr));

        quadMeshComboBox->setCurrentText(QString());
        labelQuadMetric->setText(QString());
        groupBox_18->setTitle(QCoreApplication::translate("MainWindow", "\345\233\233\351\235\242\344\275\223\347\275\221\346\240\274\350\264\250\351\207\217", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\264\250\351\207\217\346\214\207\346\240\207", nullptr));
        tetMeshComboBox->setItemText(0, QString());
        tetMeshComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\344\275\223\347\247\257", nullptr));
        tetMeshComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\347\272\265\346\250\252\346\257\224", nullptr));
        tetMeshComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\351\233\205\345\205\213\346\257\224", nullptr));
        tetMeshComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "\345\241\214\351\231\267\347\216\207", nullptr));
        tetMeshComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "\346\255\252\346\226\234\345\272\246", nullptr));
        tetMeshComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "\345\206\205\350\247\222", nullptr));
        tetMeshComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "\351\225\277\345\256\275\346\257\224", nullptr));
        tetMeshComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "\347\255\211\350\247\222\346\226\234\347\216\207", nullptr));

        tetMeshComboBox->setCurrentText(QString());
        labelTetMetric->setText(QString());
        groupBox_17->setTitle(QCoreApplication::translate("MainWindow", "\345\205\255\351\235\242\344\275\223\347\275\221\346\240\274\350\264\250\351\207\217", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\350\264\250\351\207\217\346\214\207\346\240\207", nullptr));
        hexMeshComboBox->setItemText(0, QString());
        hexMeshComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\344\275\223\347\247\257", nullptr));
        hexMeshComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\351\224\245\345\272\246", nullptr));
        hexMeshComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\351\233\205\345\205\213\346\257\224", nullptr));
        hexMeshComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "\351\225\277\345\256\275\346\257\224", nullptr));
        hexMeshComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\351\225\277\345\256\275\346\257\224", nullptr));
        hexMeshComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "\346\255\252\346\226\234\345\272\246", nullptr));
        hexMeshComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "\344\274\270\345\261\225\345\272\246", nullptr));
        hexMeshComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "\345\257\271\350\247\222\347\272\277\351\225\277\345\272\246\346\257\224\345\200\274", nullptr));
        hexMeshComboBox->setItemText(9, QCoreApplication::translate("MainWindow", "\347\233\270\345\257\271\345\244\247\345\260\217\345\271\263\346\226\271", nullptr));

        hexMeshComboBox->setCurrentText(QString());
        labelHexMetric->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\350\264\250\351\207\217", nullptr));
        funcTab->setTabText(funcTab->indexOf(TriMesh), QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274", nullptr));
#if QT_CONFIG(whatsthis)
        viewBox->setWhatsThis(QCoreApplication::translate("MainWindow", "\347\272\277", nullptr));
#endif // QT_CONFIG(whatsthis)
        outputWidget_2->setWindowTitle(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274\344\277\241\346\201\257", nullptr));
        showInformation->setText(QString());
        outputWidget->setWindowTitle(QCoreApplication::translate("MainWindow", " \346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
#if QT_CONFIG(tooltip)
        ckbSurfaceGrid->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\275\221\346\240\274\345\274\200\345\205\263</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ckbSurfaceGrid->setText(QString());
#if QT_CONFIG(tooltip)
        ckbCoordCircle->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\235\220\346\240\207\345\234\210\345\274\200\345\205\263</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ckbCoordCircle->setText(QString());
#if QT_CONFIG(tooltip)
        ckbFaceCull->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\351\235\242\345\211\224\351\231\244\345\274\200\345\205\263</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ckbFaceCull->setText(QString());
#if QT_CONFIG(tooltip)
        viewpoints->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\202\271\351\233\206</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewpoints->setText(QString());
#if QT_CONFIG(tooltip)
        viewlines->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\272\277\346\241\206</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewlines->setText(QString());
#if QT_CONFIG(tooltip)
        viewfill->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\271\263\346\273\221\351\235\242</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewfill->setText(QString());
#if QT_CONFIG(tooltip)
        viewflatfill->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\351\235\242\347\211\207</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewflatfill->setText(QString());
#if QT_CONFIG(tooltip)
        viewlight->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\205\211\347\205\247\346\250\241\345\274\217</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewlight->setText(QString());
#if QT_CONFIG(tooltip)
        viewnormal->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\346\263\225\345\220\221\346\250\241\345\274\217</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewnormal->setText(QString());
#if QT_CONFIG(tooltip)
        viewReset->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\346\263\225\345\220\221\346\250\241\345\274\217</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewReset->setText(QString());
        btnInformationClear->setText(QString());
#if QT_CONFIG(tooltip)
        btnLastMesh1->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\351\200\211\346\213\251\345\211\215\344\270\200\344\270\252\347\275\221\346\240\274</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLastMesh1->setText(QString());
#if QT_CONFIG(tooltip)
        btnNextMesh1->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\351\200\211\346\213\251\345\220\216\344\270\200\344\270\252\347\275\221\346\240\274</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnNextMesh1->setText(QString());
#if QT_CONFIG(tooltip)
        viewclear->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\345\210\240\351\231\244\345\275\223\345\211\215\347\275\221\346\240\274</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewclear->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURBINE_BLADE_H

//
// Created by WHISKING on 2022/4/26.
//

#include "ModelListView.h"

ModelListView::ModelListView(QString fileName, int vSize, int eSize, int fSize){
    setText(0,fileName);
    QTreeWidgetItem *vertSize = new QTreeWidgetItem;
    vertSize->setText(0, "vertices size");
    vertSize->setData(1, 0, vSize);
    QTreeWidgetItem *edgeSize = new QTreeWidgetItem;
    edgeSize->setText(0,"edge size");
    edgeSize->setData(1, 0, eSize);
    QTreeWidgetItem *faceSize = new QTreeWidgetItem;
    faceSize->setText(0, "face size");
    faceSize->setData(1, 0, fSize);
    addChild(vertSize);
    addChild(edgeSize);
    addChild(faceSize);
};

ModelListView::~ModelListView(){

};

void ModelListView::PrintModelMessage(){
//    ui->modelListWidget->setColumnCount(2);//设置列
//    QTreeWidgetItem* first = new QTreeWidgetItem;
//    first->setText(0,"first");
//    items.append(first);
//    ui->modelListWidget->insertTopLevelItems(0, items);
}
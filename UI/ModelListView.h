//
// Created by WHISKING on 2022/4/26.
//
#ifndef IGAMEVIEW_MODELLISTVIEW_H
#define IGAMEVIEW_MODELLISTVIEW_H
#include <QHBoxLayout>
#include <QTreeWidget>

class ModelListView : public QTreeWidgetItem {
public:
    ModelListView(QString, int , int, int);
    ~ModelListView(void);
public:
    void PrintModelMessage();
};


#endif //IGAMEVIEW_MODELLISTVIEW_H

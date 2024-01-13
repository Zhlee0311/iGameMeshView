//
// Created by WHISKING on 2022/7/7.
//

#ifndef IGAMEVIEW_METRICCHART_H
#define IGAMEVIEW_METRICCHART_H
#define barLen 20
#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <cfloat>
QT_CHARTS_USE_NAMESPACE
class MetricChart : public QWidget {
Q_OBJECT

public:
    MetricChart(QWidget *parent = 0);
    ~MetricChart();

    void LoadData(std::string _fileName, std::vector<double> _value);


private:
    QChart *m_ptrChart;
    QChartView *m_ptrChartview;
    QHorizontalBarSeries *m_ptrHorizontalBarSeries;
    QBarCategoryAxis *m_ptrAxisY;
    QValueAxis *m_ptrAxisX;

    std::string valueName;
    std::vector<double> value;
    int vArr[barLen];
    double vIdx[barLen];
    int maxNum = 0;
    void ProcessingData();
    void PrintChart();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};


#endif //IGAMEVIEW_METRICCHART_H

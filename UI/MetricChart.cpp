//
// Created by WHISKING on 2022/7/7.
//

#include "MetricChart.h"

#include <utility>


MetricChart::MetricChart(QWidget *parent)
        : QWidget(parent)
        , m_ptrChart(new QChart)
        , m_ptrChartview(new QChartView(m_ptrChart, this))
        , m_ptrHorizontalBarSeries(new QHorizontalBarSeries)
{
    //setWindowTitle(tr("水平柱状图样例 "));
    m_ptrChart->setMinimumSize(220, 630);
    //m_ptrChart->setMaximumSize(1000,1000);
    //m_ptrChartview->setFixedSize(210, 620);
    m_ptrChart->addSeries(m_ptrHorizontalBarSeries);
    //m_ptrChart->setTitle("水平柱状图样例 ");
    m_ptrChart->setAnimationOptions(QChart::AllAnimations);
    //ProcessingData();
    PrintChart();
}

MetricChart::~MetricChart() {}

void MetricChart::LoadData(std::string _valueName, std::vector<double> _value){
    valueName = std::move(_valueName);
    value = std::move(_value);
    ProcessingData();
    PrintChart();
}

void MetricChart::ProcessingData()
{
    for(int i=0; i < barLen; i++){
        vArr[i] = 0;
    }
    double vMax = DBL_MIN;
    double vMin = DBL_MAX;
    int n = value.size();
    for(int i=0;i<n;i++){
        vMax = std::max(vMax,value[i]);
        vMin = std::min(vMin,value[i]);
    }
    double range = vMax - vMin;
    double smallRange = range / barLen;
    double scale = 1.0;
    //if(vMin < 0.0006) scale = 1000.0;
    for(int i=0; i < barLen; i++){
        vIdx[i] = (vMin + i*smallRange)*scale;
    }
    for(int i=0;i<n;i++){
        double diff = value[i]-vMin;
        int idx = diff/smallRange;
        vArr[idx]++;
    }
    maxNum = -1;
    for(int i=0; i < barLen; i++){
        maxNum = std::max(maxNum, vArr[i]);
    }
}


void MetricChart::PrintChart()
{
    m_ptrAxisY = new QBarCategoryAxis;
    m_ptrAxisX = new QValueAxis;
    m_ptrHorizontalBarSeries->clear();

    for(int i=0; i < barLen; i++){
        m_ptrAxisY->append(QString::number(vIdx[i],'d',3));
    }
    int maxLen = 4-(maxNum%4) + maxNum;
    m_ptrAxisX->setRange(0, maxLen);
    m_ptrAxisX->setTickCount(4);
    m_ptrAxisX->setLabelFormat("%d");
    m_ptrChart->setAxisX(m_ptrAxisX, m_ptrHorizontalBarSeries);
    m_ptrChart->setAxisY(m_ptrAxisY, m_ptrHorizontalBarSeries);

    QBarSet* barSet = new QBarSet(QString::fromStdString(valueName));
    for(int i=0; i < barLen; i++){
        *barSet << vArr[i];
    }
    m_ptrHorizontalBarSeries->append(barSet);

    // 构建不同的 QAbstractBarSeries
//    std::vector<QBarSet*> sets(100);
//    for(int i=0;i<sets.size();i++){
//        sets[i] = new QBarSet("");
//        *sets[i] << i+1;
//        sets[i]->setColor(QColor(255,i,i));
//        m_ptrHorizontalBarSeries->append(sets[i]);
//    }
//    *set1 << 5 << 2 << 3 << 4 << 4 << 7;
//    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
//    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
//    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    // 柱状图

//    m_ptrHorizontalBarSeries->append(set0);
//    m_ptrHorizontalBarSeries->append(set1);
//    m_ptrHorizontalBarSeries->append(set2);
//    m_ptrHorizontalBarSeries->append(set3);
//    m_ptrHorizontalBarSeries->append(set4);
}

void MetricChart::mousePressEvent(QMouseEvent *event)
{
    QList<qreal> temp;
    foreach (auto item, m_ptrHorizontalBarSeries->barSets()) {
        for (int i = 0; i < item->count(); i++) {
            temp.insert(i,(*item)[i]);
            //item->remove(i,item->count());
        }
        item->remove(0,item->count());
    }
    foreach (auto item, m_ptrHorizontalBarSeries->barSets()) {
        for (int i = 0; i < m_ptrAxisY->count(); i++) {
            //item->append(qrand() % 20);
            //item->insert(i,temp[i]);
        }
        item->append(temp);
    }
}

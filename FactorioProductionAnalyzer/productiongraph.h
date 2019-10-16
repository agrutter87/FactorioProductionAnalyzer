#ifndef PRODUCTIONGRAPH_H
#define PRODUCTIONGRAPH_H

#include <QObject>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>

#include "product.h"

typedef struct
{
    QtCharts::QLineSeries           *lineSeries;
    int                             numDataToAvg;
} ProductionAnalyzerSeries;

class ProductionGraph
{
    Q_GADGET

public:
    ProductionGraph();

    QtCharts::QChart                    *chart;
    QtCharts::QChartView                *chartView;
    QtCharts::QValueAxis                *timestampAxisX;
    QtCharts::QValueAxis                *timestampAxisY;
    QtCharts::QLineSeries               *mainLineSeries;
    QVector<ProductionAnalyzerSeries>   productionAnalyzerSeries;
    Product                             product;
    qreal                               x;
    qreal                               minValue;
    qreal                               maxValue;
    qreal                               prevValue;
    bool                                firstTime;
};

#endif // PRODUCTIONGRAPH_H

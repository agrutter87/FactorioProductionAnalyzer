#ifndef PRODUCTIONGRAPH_H
#define PRODUCTIONGRAPH_H

#include <QObject>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>

#include "product.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_PRODUCTION_GRAPH  (1)

/*************************************************************************
 * ProductionGraph Class
 *************************************************************************/
class ProductionGraph
{
    Q_GADGET

public:
    typedef struct
    {
        QtCharts::QLineSeries           *lineSeries;
        int                             numDataToAvg;
    } ProductionAnalyzerSeries;

                                        ProductionGraph(Product::ProductType productType,
                                                        QWidget *parent = nullptr,
                                                        QString name = "Unnamed");
                                        ~ProductionGraph();

    void                                update();
    Product                             getProduct() const;
    void                                setProduct(Product product);
    QtCharts::QChartView                *getChartView() const;

private:
    QtCharts::QChart                    *mChart;
    QtCharts::QChartView                *mChartView;
    QtCharts::QLineSeries               *mMainLineSeries;
    QVector<ProductionAnalyzerSeries>   mProductionAnalyzerSeries;
    QtCharts::QValueAxis                *mTimestampAxisX;
    QtCharts::QValueAxis                *mTimestampAxisY;
    Product                             mProduct;
    qreal                               mX;
    qreal                               mMinValue;
    qreal                               mMaxValue;
    qreal                               mPrevValue;
    bool                                mFirstTime;
};

#endif // PRODUCTIONGRAPH_H

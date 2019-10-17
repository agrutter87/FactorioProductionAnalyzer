#include "productiongraph.h"
#include "productionanalyzer.h"

/*************************************************************************
 * ProductionGraph::ProductionGraph
 *************************************************************************/
ProductionGraph::ProductionGraph(Product::ProductType productType, QWidget* parent, QString name)
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Initialize ProductionGraph */
    mProduct.setName(name);
    mProduct.setProductType(productType);
    mX = 0;
    mMinValue = 999999999;
    mMaxValue = 0;
    mPrevValue = 0;
    mFirstTime = true;

    /* Create QChart */
    mChart = new QtCharts::QChart();

    /* Create QChartView */
    mChartView = new QtCharts::QChartView(mChart, parent);

    /* Create QAxes */
    mTimestampAxisX = new QtCharts::QValueAxis;
    mTimestampAxisY = new QtCharts::QValueAxis;

    /* Create QLineSeries' */
    mMainLineSeries = new QtCharts::QLineSeries();

    ProductionAnalyzerSeries productionAnalyzerSeries;
    productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
    productionAnalyzerSeries.numDataToAvg = 10;
    mProductionAnalyzerSeries.append(productionAnalyzerSeries);

    productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
    productionAnalyzerSeries.numDataToAvg = 15;
    mProductionAnalyzerSeries.append(productionAnalyzerSeries);

    /* Add QLineSeries' to QChart */
    mChart->addSeries(mMainLineSeries);
    for(int i = 0; i < mProductionAnalyzerSeries.count(); i++)
    {
        mChart->addSeries(mProductionAnalyzerSeries[i].lineSeries);
    }

    /* Configure QChart */
    mChart->setTitle(name);
    //productionGraph.chart->legend()->hide();

    /* Add QAxes to QChart */
    mChart->addAxis(mTimestampAxisX, Qt::AlignBottom);
    mChart->addAxis(mTimestampAxisY, Qt::AlignLeft);

    /* Attach QLineSeries' to QAxes */
    mMainLineSeries->attachAxis(mTimestampAxisY);
    mMainLineSeries->attachAxis(mTimestampAxisX);
    mMainLineSeries->setName(name);
    for(int i = 0; i < mProductionAnalyzerSeries.count(); i++)
    {
        mProductionAnalyzerSeries[i].lineSeries->attachAxis(mTimestampAxisY);
        mProductionAnalyzerSeries[i].lineSeries->attachAxis(mTimestampAxisX);
        mProductionAnalyzerSeries[i].lineSeries->setName(name+"-avg-over-"+QString::number(mProductionAnalyzerSeries[i].numDataToAvg));
    }

    /* Configure QChartView */
    mChartView->setRenderHint(QPainter::Antialiasing);
}

/*************************************************************************
 * ProductionGraph::~ProductionGraph
 *************************************************************************/
ProductionGraph::~ProductionGraph()
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    delete mChartView;
    delete mChart;
}

/*************************************************************************
 * ProductionGraph::update
 *************************************************************************/
void ProductionGraph::update()
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    qreal curValue = 0;
    qreal outValue = 0;

    /* Get the value */
    curValue = mProduct.getValue();

    /* If this is the first data point read from the file... */
    if(mFirstTime)
    {
        /* Set the outValue (a change between readings) to 0 to avoid huge value from first reading of file */
        outValue = 0;

        mFirstTime = false;
    }
    else
    {
        /* Calculate the change from the previous count to now */
        outValue = curValue - mPrevValue;
    }

    /* Set the prevValue to use for calculating the change on the next data reading */
    mPrevValue = curValue;

    /* Expand the scale of the graph downward to fit the data if necessary */
    if(outValue < mMinValue)
    {
        mMinValue = outValue;
    }

    /* Expand the scale of the graph upward to fit the data if necessary */
    if(outValue > mMaxValue)
    {
        mMaxValue = outValue;
    }

    /* Append the data to the main lineSeries */
    mMainLineSeries->append(mX, outValue);
    if(mMainLineSeries->count() > PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
    {
        mMainLineSeries->removePoints(mMainLineSeries->count() - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX, 1);
    }

    /* For each series on this graph */
    for(int j = 0; j < mProductionAnalyzerSeries.count(); j++)
    {
        /* Average most current values in line series to smooth things out */
        int index_max = mMainLineSeries->count() - 1;
        int avg_count = mProductionAnalyzerSeries[j].numDataToAvg;
        if(index_max > avg_count)
        {
            outValue = 0;
            for(int k = index_max; k > index_max - avg_count; k--)
            {
                outValue += mMainLineSeries->at(k).y();
            }
            outValue /= avg_count;

            mProductionAnalyzerSeries[j].lineSeries->append(mX, outValue);
            if(mProductionAnalyzerSeries[j].lineSeries->count() > PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
            {
                mProductionAnalyzerSeries[j].lineSeries->removePoints(mProductionAnalyzerSeries[j].lineSeries->count() - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX, 1);
            }
        }
    }

    /* Set min/max values for axes using the values saved above */
    mTimestampAxisY->setMax(mMaxValue);
    mTimestampAxisY->setMin(mMinValue);

    /* Set max x if the x value is larger than the current max */
    if(mX > mTimestampAxisX->max())
    {
        mTimestampAxisX->setMax(mX);

        /* Set the min higher to keep it "scrolling" once it fills the time span */
        if(mX >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
        {
            mTimestampAxisX->setMin(mX - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
        }
    }

    /* Increment x for the next go around */
    mX = mX + 1;
}

/*************************************************************************
 * ProductionGraph::getProduct
 *************************************************************************/
Product ProductionGraph::getProduct() const
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mProduct;
}

/*************************************************************************
 * ProductionGraph::setProduct
 *************************************************************************/
void ProductionGraph::setProduct(Product product)
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mProduct = product;
}

/*************************************************************************
 * ProductionGraph::getChartView
 *************************************************************************/
QtCharts::QChartView *ProductionGraph::getChartView() const
{
#if DEBUG_PRODUCTION_GRAPH
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mChartView;
}

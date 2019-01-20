#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "productionanalyzer.h"

#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /* Setup Qt Designer part of the UI */
    ui->setupUi(this);

    /* Create a timer to use for periodic reading of the Factorio mod output data file */
    periodicReadTimer = new QTimer(this);
    connect(periodicReadTimer, SIGNAL(timeout()), this, SLOT(on_signalPeriodicReadTimer_timeout()));

    /* Create HBOXLAYOUT_MAX number of QHBoxLayout rows */
    for(int i = 0; i < HBOXLAYOUTS_MAX; i++)
    {
        mHBoxLayouts[i] = new QHBoxLayout();
        mHBoxLayouts[i]->setSpacing(6);
        mHBoxLayouts[i]->setObjectName(QString("horizontalLayout"+QString().number(i)));

        ui->verticalLayout->addLayout(mHBoxLayouts[i]);
    }

    /* Create TABWIDGETS_MAX number of QTabWidgets and set them to their positions in the layouts */
    for(int i = 0; i < TABWIDGETS_MAX; i++)
    {
        static int j = 0;

        /* Create a new QTabWidget and store the pointer in our array */
        mTabWidgets[i] = new QTabWidget();
        mTabWidgets[i]->hide();

        /* Start a new row if needed to fill the HBOXLAYOUTS_MAX number of horizontal layouts */
        if(i > 0 && i % (TABWIDGETS_MAX / HBOXLAYOUTS_MAX) == 0)
        {
            j++;
        }

        /* Add the new QTabWidget to the horizontal layout */
        mHBoxLayouts[j]->addWidget(mTabWidgets[i]);
    }

    /* Examples for how to create the charts */
    createChart("iron-ore",         mTabWidgets[0], Product::Input);
    createChart("copper-ore",       mTabWidgets[0], Product::Input);
    createChart("coal",             mTabWidgets[0], Product::Input);
    createChart("iron-plate",       mTabWidgets[1], Product::Input);
    createChart("copper-plate",     mTabWidgets[1], Product::Input);
    createChart("science-pack-1",   mTabWidgets[2], Product::Input);
    createChart("iron-ore",         mTabWidgets[3], Product::Output);
    createChart("copper-ore",       mTabWidgets[3], Product::Output);
    createChart("coal",             mTabWidgets[3], Product::Output);
    createChart("iron-plate",       mTabWidgets[4], Product::Output);
    createChart("copper-plate",     mTabWidgets[4], Product::Output);
    createChart("science-pack-1",   mTabWidgets[5], Product::Output);
}

MainWindow::~MainWindow()
{
    delete periodicReadTimer;
    delete ui;
}

/*************************************************************************
 * MENU ACTIONS
 *************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
    /* Set the strings used in the getOpenFileName dialog */
    QString fileDialogCaption = "Open File";
#ifdef WIN32
    QString fileDialogPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Factorio/script-output/FactorioProductionAnalzyer/production_data.json";
#else
    QString fileDialogPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.factorio/script-output/FactorioProductionAnalyzer/production_data.json";
#endif
    QString fileDialogFilter = "JSON (*.json);;DAT (*.dat)";
    QString fileDialogFilterDefault = "JSON (*.json)";

    /* Open the getOpenFileName dialog and wait for selection */
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    fileDialogCaption,
                                                    fileDialogPath,
                                                    fileDialogFilter,
                                                    &fileDialogFilterDefault);

    /* If the filename is valid... */
    if(!fileName.isEmpty())
    {
        /* If the file is a JSON file... */
        if(fileName.contains(".json"))
        {
            /* Set the file information as a JSON file */
            mProductionAnalyzer.setFile(ProductionAnalyzer::Json, fileName);
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
        else if(fileName.contains(".dat"))
        {
            /* Otherwise set it as a Binary file */
            mProductionAnalyzer.setFile(ProductionAnalyzer::Binary, fileName);
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
    }
}

void MainWindow::on_actionNewChart_triggered()
{

}


/*************************************************************************
 * SLOT ACTIONS
 *************************************************************************/
void MainWindow::on_signalPeriodicReadTimer_timeout(void)
{
    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    updateCharts();
}

/*************************************************************************
 * MainWindow::createChart
 *************************************************************************/
void MainWindow::createChart(const QString &name, QTabWidget *tabWidget, Product::ProductType productType)
{
    /* Create ProductionAnalyzerGraph */
    ProductionAnalyzerGraph productionAnalyzerGraph;
    productionAnalyzerGraph.product.setName(name);
    productionAnalyzerGraph.product.setProductType(productType);
    productionAnalyzerGraph.x = 0;
    productionAnalyzerGraph.minValue = 999999999;
    productionAnalyzerGraph.maxValue = 0;
    productionAnalyzerGraph.prevValue = 0;
    productionAnalyzerGraph.firstTime = true;

    /* Create QChart */
    productionAnalyzerGraph.chart = new QtCharts::QChart();

    /* Create QChartView */
    productionAnalyzerGraph.chartView = new QtCharts::QChartView(productionAnalyzerGraph.chart, ui->centralWidget);

    /* Create QAxes */
    productionAnalyzerGraph.timestampAxisX = new QtCharts::QValueAxis;
    productionAnalyzerGraph.timestampAxisY = new QtCharts::QValueAxis;

    /* Create QLineSeries' */
    productionAnalyzerGraph.mainLineSeries = new QtCharts::QLineSeries();

    ProductionAnalyzerSeries productionAnalyzerSeries;
    productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
    productionAnalyzerSeries.numDataToAvg = 10;
    productionAnalyzerGraph.productionAnalyzerSeries.append(productionAnalyzerSeries);

    productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
    productionAnalyzerSeries.numDataToAvg = 15;
    productionAnalyzerGraph.productionAnalyzerSeries.append(productionAnalyzerSeries);

    /* Add QLineSeries' to QChart */
    productionAnalyzerGraph.chart->addSeries(productionAnalyzerGraph.mainLineSeries);
    for(int i = 0; i < productionAnalyzerGraph.productionAnalyzerSeries.count(); i++)
    {
        productionAnalyzerGraph.chart->addSeries(productionAnalyzerGraph.productionAnalyzerSeries[i].lineSeries);
    }

    /* Configure QChart */
    productionAnalyzerGraph.chart->setTitle(name);
    //productionAnalyzerGraph.chart->legend()->hide();

    /* Add QAxes to QChart */
    productionAnalyzerGraph.chart->addAxis(productionAnalyzerGraph.timestampAxisX, Qt::AlignBottom);
    productionAnalyzerGraph.chart->addAxis(productionAnalyzerGraph.timestampAxisY, Qt::AlignLeft);

    /* Attach QLineSeries' to QAxes */
    productionAnalyzerGraph.mainLineSeries->attachAxis(productionAnalyzerGraph.timestampAxisY);
    productionAnalyzerGraph.mainLineSeries->attachAxis(productionAnalyzerGraph.timestampAxisX);
    productionAnalyzerGraph.mainLineSeries->setName(name);
    for(int i = 0; i < productionAnalyzerGraph.productionAnalyzerSeries.count(); i++)
    {
        productionAnalyzerGraph.productionAnalyzerSeries[i].lineSeries->attachAxis(productionAnalyzerGraph.timestampAxisY);
        productionAnalyzerGraph.productionAnalyzerSeries[i].lineSeries->attachAxis(productionAnalyzerGraph.timestampAxisX);
        productionAnalyzerGraph.productionAnalyzerSeries[i].lineSeries->setName(name+"-avg-over-"+QString::number(productionAnalyzerGraph.productionAnalyzerSeries[i].numDataToAvg));
    }

    /* Configure QChartView */
    productionAnalyzerGraph.chartView->setRenderHint(QPainter::Antialiasing);

    /* Add a new tab to the QTabView where this will be placed */
    tabWidget->addTab(productionAnalyzerGraph.chartView, name);
    tabWidget->show();

    /* Add now fully configured ProductionAnalyzerGraphs to QVector */
    mProductionAnalyzerGraphs.append(productionAnalyzerGraph);
}

/*************************************************************************
 * MainWindow::updateCharts
 *************************************************************************/
void MainWindow::updateCharts()
{
    QVector<Product> newInputs;
    QVector<Product> newOutputs;
    qreal curValue = 0;
    qreal outValue = 0;

    /* Get the latest production inputs */
    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();

    /* Get the latest production inputs */
    newOutputs = mProductionAnalyzer.getProductionData().last().getOutputs();

    /* Loop through and update each graph */
    for(int i = 0; i < mProductionAnalyzerGraphs.size(); i++)
    {
        QVector<Product> products;
        switch(mProductionAnalyzerGraphs[i].product.getProductType())
        {
            case Product::Input:
                products = newInputs;
            break;

            case Product::Output:
                products = newOutputs;
            break;
        }

        /* Look through the products available in the file */
        foreach (const Product &product, products)
        {
            /* If we find the data meant for this graph... */
            if(product.getName() == mProductionAnalyzerGraphs[i].product.getName())
            {
                /* Get the value */
                curValue = product.getValue();

                /* If this is the first data point read from the file... */
                if(mProductionAnalyzerGraphs[i].firstTime)
                {
                    /* Set the outValue (a change between readings) to 0 to avoid huge value from first reading of file */
                    outValue = 0;

                    mProductionAnalyzerGraphs[i].firstTime = false;
                }
                else
                {
                    /* Calculate the change from the previous count to now */
                    outValue = curValue - mProductionAnalyzerGraphs[i].prevValue;
                }

                /* Set the preValue to use for calculating the change on the next data reading */
                mProductionAnalyzerGraphs[i].prevValue = curValue;

                /* Expand the scale of the graph downward to fit the data if necessary */
                if(outValue < mProductionAnalyzerGraphs[i].minValue)
                {
                    mProductionAnalyzerGraphs[i].minValue = outValue;
                }

                /* Expand the scale of the graph upward to fit the data if necessary */
                if(outValue > mProductionAnalyzerGraphs[i].maxValue)
                {
                    mProductionAnalyzerGraphs[i].maxValue = outValue;
                }

                /* Append the data to the main lineSeries */
                mProductionAnalyzerGraphs[i].mainLineSeries->append(mProductionAnalyzerGraphs[i].x, outValue);

                /* For each series on this ith graph */
                for(int j = 0; j < mProductionAnalyzerGraphs[i].productionAnalyzerSeries.count(); j++)
                {
                    /* Average most current values in line series to smooth things out */
                    int index_max = mProductionAnalyzerGraphs[i].mainLineSeries->count() - 1;
                    int avg_count = mProductionAnalyzerGraphs[i].productionAnalyzerSeries[j].numDataToAvg;
                    if(index_max > avg_count)
                    {
                        outValue = 0;
                        for(int k = index_max; k > index_max - avg_count; k--)
                        {
                            outValue += mProductionAnalyzerGraphs[i].mainLineSeries->at(k).y();
                        }
                        outValue /= avg_count;

                        mProductionAnalyzerGraphs[i].productionAnalyzerSeries[j].lineSeries->append(mProductionAnalyzerGraphs[i].x, outValue);
                    }
                }
            }
        }

        /* Set min/max values for axes using the values saved above */
        mProductionAnalyzerGraphs[i].timestampAxisY->setMax(mProductionAnalyzerGraphs[i].maxValue);
        mProductionAnalyzerGraphs[i].timestampAxisY->setMin(mProductionAnalyzerGraphs[i].minValue);

        /* Set max x if the x value is larger than the current max */
        if(mProductionAnalyzerGraphs[i].x > mProductionAnalyzerGraphs[i].timestampAxisX->max())
        {
            mProductionAnalyzerGraphs[i].timestampAxisX->setMax(mProductionAnalyzerGraphs[i].x);

            /* Set the min higher to keep it "scrolling" once it fills the time span */
            if(mProductionAnalyzerGraphs[i].x >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
            {
                mProductionAnalyzerGraphs[i].timestampAxisX->setMin(mProductionAnalyzerGraphs[i].x - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
            }
        }

        /* Increment x for the next go around */
        mProductionAnalyzerGraphs[i].x = mProductionAnalyzerGraphs[i].x + 1;
    }
}

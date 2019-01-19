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
    ui->setupUi(this);

    periodicReadTimer = new QTimer(this);
    connect(periodicReadTimer, SIGNAL(timeout()), this, SLOT(periodicRead()));

    createChart("iron-ore");
    createChart("copper-ore");
    createChart("coal");
    createChart("iron-plate");
    createChart("copper-plate");
    createChart("science-pack-1");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete periodicReadTimer;
}

/*************************************************************************
 * MENU ACTIONS
 *************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
    qDebug("MainWindow::on_actionOpen_triggered");

    QString fileDialogCaption = "Caption";
#ifdef WIN32
    QString fileDialogPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/AppData/Roaming/Factorio/script-output/FactorioProductionAnalzyer/production_data.json";
#else
    QString fileDialogPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.factorio/script-output/FactorioProductionAnalyzer/production_data.json";
#endif
    QString fileDialogFilter = "JSON (*.json);;DAT (*.dat)";
    QString fileDialogFilterDefault = "JSON (*.json)";
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    fileDialogCaption,
                                                    fileDialogPath,
                                                    fileDialogFilter,
                                                    &fileDialogFilterDefault);
    if(!fileName.isEmpty())
    {
        if(fileName.contains(".json"))
        {
            mProductionAnalyzer.setFile(ProductionAnalyzer::Json, fileName);
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
        else if(fileName.contains(".dat"))
        {
            mProductionAnalyzer.setFile(ProductionAnalyzer::Binary, fileName);
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
    }
}

/*************************************************************************
 * SLOT ACTIONS
 *************************************************************************/
void MainWindow::periodicRead(void)
{
    updateCharts();
}

/*************************************************************************
 * MainWindow::createChart
 *************************************************************************/
void MainWindow::createChart(const QString &name)
{
    static QHBoxLayout *currentHorizontalLayout = ui->horizontalLayout;

    /* Create ProductionAnalyzerGraph */
    ProductionAnalyzerGraph productionAnalyzerGraph;
    productionAnalyzerGraph.product.setName(name);
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

    /* Configure Qt Layouts */
    if((mProductionAnalyzerGraphs.size() % NUM_CHARTS_PER_ROW) == 0)
    {
        QHBoxLayout *horizontalLayout;
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        ui->verticalLayout->addLayout(horizontalLayout);
        currentHorizontalLayout = horizontalLayout;
    }

    /* Add QChartView to Qt Layout */
    currentHorizontalLayout->addWidget(productionAnalyzerGraph.chartView);

    /* Add now fully configured ProductionAnalyzerGraphs to QVector */
    mProductionAnalyzerGraphs.append(productionAnalyzerGraph);
}

/*************************************************************************
 * MainWindow::updateCharts
 *************************************************************************/
void MainWindow::updateCharts()
{
    QVector<Product> newInputs;
    qreal curValue = 0;
    qreal outValue = 0;

    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();

    /* Loop through and update each graph */
    for(int i = 0; i < mProductionAnalyzerGraphs.size(); i++)
    {
        /* Look through the products available in the file */
        foreach (const Product &product, newInputs)
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

        mProductionAnalyzerGraphs[i].timestampAxisY->setMax(mProductionAnalyzerGraphs[i].maxValue);
        mProductionAnalyzerGraphs[i].timestampAxisY->setMin(mProductionAnalyzerGraphs[i].minValue);

        if(mProductionAnalyzerGraphs[i].x > mProductionAnalyzerGraphs[i].timestampAxisX->max())
        {
            mProductionAnalyzerGraphs[i].timestampAxisX->setMax(mProductionAnalyzerGraphs[i].x);

            if(mProductionAnalyzerGraphs[i].x >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
            {
                mProductionAnalyzerGraphs[i].timestampAxisX->setMin(mProductionAnalyzerGraphs[i].x - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
            }
        }

        mProductionAnalyzerGraphs[i].x = mProductionAnalyzerGraphs[i].x + 1;
    }
}

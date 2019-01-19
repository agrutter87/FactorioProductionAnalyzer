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

void MainWindow::createChart(const QString &name)
{
    ProductionAnalyzerGraph productionAnalyzerGraph;
    productionAnalyzerGraph.product.setName(name);

    productionAnalyzerGraph.x = 0;
    productionAnalyzerGraph.minValue = 999999999;
    productionAnalyzerGraph.maxValue = 0;
    productionAnalyzerGraph.prevValue = 0;
    productionAnalyzerGraph.firstTime = true;
    productionAnalyzerGraph.chart = new QtCharts::QChart();
    productionAnalyzerGraph.chartView = new QtCharts::QChartView(productionAnalyzerGraph.chart, ui->centralWidget);

    productionAnalyzerGraph.timestampAxisX = new QtCharts::QValueAxis;
    productionAnalyzerGraph.timestampAxisY = new QtCharts::QValueAxis;

    productionAnalyzerGraph.lineSeries = new QtCharts::QLineSeries();

    productionAnalyzerGraph.chart->addSeries(productionAnalyzerGraph.lineSeries);

    productionAnalyzerGraph.chart->setTitle(name);
    productionAnalyzerGraph.chart->legend()->hide();
    productionAnalyzerGraph.chart->addAxis(productionAnalyzerGraph.timestampAxisX, Qt::AlignBottom);
    productionAnalyzerGraph.chart->addAxis(productionAnalyzerGraph.timestampAxisY, Qt::AlignLeft);

    productionAnalyzerGraph.lineSeries->attachAxis(productionAnalyzerGraph.timestampAxisY);
    productionAnalyzerGraph.lineSeries->attachAxis(productionAnalyzerGraph.timestampAxisX);
    productionAnalyzerGraph.lineSeries->setName(name);

    productionAnalyzerGraph.chartView->setRenderHint(QPainter::Antialiasing);

    ui->horizontalLayout->addWidget(productionAnalyzerGraph.chartView);

    mProductionAnalyzerGraphs.append(productionAnalyzerGraph);
}

void MainWindow::updateCharts()
{
    QVector<Product> newInputs;
    qreal curValue = 0;
    qreal prodValue = 0;

    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();

    for(int i = 0; i < mProductionAnalyzerGraphs.size(); i++)
    {
        foreach (const Product &product, newInputs)
        {
            if(product.getName().contains(mProductionAnalyzerGraphs[i].product.getName()))
            {
                qDebug() << mProductionAnalyzerGraphs[i].product.getName() << "found";

                curValue = product.getValue();
                qDebug() << "curValue = " << curValue;
                qDebug() << "firstTime = " << mProductionAnalyzerGraphs[i].firstTime;

                if(mProductionAnalyzerGraphs[i].firstTime)
                {
                    prodValue = 0;
                    mProductionAnalyzerGraphs[i].prevValue = curValue;
                    mProductionAnalyzerGraphs[i].firstTime = false;
                }
                else
                {
                    prodValue = curValue - mProductionAnalyzerGraphs[i].prevValue;
                    mProductionAnalyzerGraphs[i].prevValue = curValue;
                }
                qDebug() << "prodValue = " << prodValue;

                if(prodValue < mProductionAnalyzerGraphs[i].minValue)
                {
                    mProductionAnalyzerGraphs[i].minValue = prodValue;
                }

                if(prodValue > mProductionAnalyzerGraphs[i].maxValue)
                {
                    mProductionAnalyzerGraphs[i].maxValue = prodValue;
                }

                mProductionAnalyzerGraphs[i].lineSeries->append(mProductionAnalyzerGraphs[i].x, prodValue);
            }
        }

        mProductionAnalyzerGraphs[i].timestampAxisY->setMax(mProductionAnalyzerGraphs[i].maxValue);
        mProductionAnalyzerGraphs[i].timestampAxisY->setMin(mProductionAnalyzerGraphs[i].minValue);

        if(mProductionAnalyzerGraphs[i].x > mProductionAnalyzerGraphs[i].timestampAxisX->max())
        {
            mProductionAnalyzerGraphs[i].timestampAxisX->setMax(mProductionAnalyzerGraphs[i].x);

    /* Enable this if you only want to see the data which is available in the QVector of ProductionData: */
    #if (0)
            if(mProductionAnalyzerGraphs[i].x >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
            {
                mProductionAnalyzerGraphs[i].timestampAxisX->setMin(mProductionAnalyzerGraphs[i].x - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
            }
    #endif
        }

        mProductionAnalyzerGraphs[i].x = mProductionAnalyzerGraphs[i].x + 1;
    }
}

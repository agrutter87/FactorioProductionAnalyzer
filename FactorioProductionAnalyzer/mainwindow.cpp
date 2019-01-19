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

    createChart();
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
    updateChart();
}

void MainWindow::createChart()
{
    mChart = new QtCharts::QChart();
    mChartView = new QtCharts::QChartView(mChart, ui->centralWidget);

    mTimestampAxisX = new QtCharts::QValueAxis;
    mTimestampAxisY = new QtCharts::QValueAxis;

    mLineSeries = new QtCharts::QLineSeries();
    mLineSeries2 = new QtCharts::QLineSeries();

    mChart->addSeries(mLineSeries);
    mChart->addSeries(mLineSeries2);

    mChart->setTitle("Timestamp Chart");
    mChart->addAxis(mTimestampAxisX, Qt::AlignBottom);
    mChart->addAxis(mTimestampAxisY, Qt::AlignLeft);

    mLineSeries->attachAxis(mTimestampAxisY);
    mLineSeries->attachAxis(mTimestampAxisX);
    mLineSeries->setName("copper-plate");

    mLineSeries2->attachAxis(mTimestampAxisY);
    mLineSeries2->attachAxis(mTimestampAxisX);
    mLineSeries2->setName("iron-plate");

    mChartView->setRenderHint(QPainter::Antialiasing);

    ui->horizontalLayout->addWidget(mChartView);
}

void MainWindow::updateChart()
{
    static qreal x = 0;
    QVector<Product> newInputs;
    static qreal minValue = 999999999;
    static qreal maxValue = 0;
    qreal curValue = 0;
    static qreal prevValue = 0;
    static qreal prevValue2 = 0;
    static bool firstTime = true;
    static bool firstTime2 = true;
    qreal prodValue = 0;

    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();
    foreach (const Product product, newInputs)
    {
        if(product.getName().contains("copper-plate"))
        {
            qDebug("copper-plate found");

            curValue = product.getValue();

            if(firstTime)
            {
                prodValue = 0;
                prevValue = curValue;
                firstTime = false;
            }
            else
            {
                prodValue = curValue - prevValue;
                prevValue = curValue;
            }

            if(prodValue < minValue)
            {
                minValue = prodValue;
            }

            if(prodValue > maxValue)
            {
                maxValue = prodValue;
            }

            mLineSeries->append(x, prodValue);
        }
        else if(product.getName().contains("iron-plate"))
        {
            qDebug("iron-plate found");
            curValue = product.getValue();
            if(firstTime2)
            {
                prodValue = 0;
                prevValue2 = curValue;
                firstTime2 = false;
            }
            else
            {
                prodValue = curValue - prevValue2;
                prevValue2 = curValue;
            }

            if(prodValue < minValue)
            {
                minValue = prodValue;
            }

            if(prodValue > maxValue)
            {
                maxValue = prodValue;
            }

            mLineSeries2->append(x, prodValue);
        }
    }

    mTimestampAxisY->setMax(maxValue);
    mTimestampAxisY->setMin(minValue);

    if(x > mTimestampAxisX->max())
    {
        mTimestampAxisX->setMax(x);

/* Enable this if you only want to see the data which is available in the QVector of ProductionData: */
#if 0
        if(x >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
        {
            mTimestampAxisX->setMin(x - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
        }
#endif
    }

    x = x + 1;
}

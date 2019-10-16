#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "productionanalyzer.h"
#include "productiongraph.h"

#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

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
        mTabWidgets[i]->setTabsClosable(true);
        mTabWidgets[i]->setMovable(true);
        switch(i)
        {
        case 0:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_0(int)));
            break;

        case 1:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_1(int)));
            break;

        case 2:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_2(int)));
            break;

        case 3:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_3(int)));
            break;

        case 4:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_4(int)));
            break;

        case 5:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_5(int)));
            break;

        case 6:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_6(int)));
            break;

        case 7:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_7(int)));
            break;

        case 8:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(on_signalTabWidget_tabCloseRequested_8(int)));
            break;
        default:
            break;
        }
        mTabWidgets[i]->hide();

        /* Start a new row if needed to fill the HBOXLAYOUTS_MAX number of horizontal layouts */
        if(i > 0 && i % (TABWIDGETS_MAX / HBOXLAYOUTS_MAX) == 0)
        {
            j++;
        }

        /* Add the new QTabWidget to the horizontal layout */
        mHBoxLayouts[j]->addWidget(mTabWidgets[i]);
    }

    mNewChartOkButton_released = false;
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
            mProductionAnalyzer.fileRead();
            populateItemList();
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
        else if(fileName.contains(".dat"))
        {
            /* Otherwise set it as a Binary file */
            mProductionAnalyzer.setFile(ProductionAnalyzer::Binary, fileName);
            mProductionAnalyzer.fileRead();
            populateItemList();
            periodicReadTimer->start(PRODUCTION_DATA_READ_PERIOD_MS);
        }
    }
}

void MainWindow::on_actionNewChart_triggered()
{
    mNewChartDialog = new QDialog();
    mNewChartDialog->setModal(true);
    mNewChartDialog->setWindowTitle("Configure Chart");
    mNewChartDialog->setGeometry(this->x() + 300, this->y() + 300, 300, 100);

    QVBoxLayout *verticalLayout = new QVBoxLayout(mNewChartDialog);

    QHBoxLayout *horizontalLayout1 = new QHBoxLayout();
    QHBoxLayout *horizontalLayout2 = new QHBoxLayout();
    QHBoxLayout *horizontalLayout3 = new QHBoxLayout();
    QHBoxLayout *horizontalLayout4 = new QHBoxLayout();

    QLabel *itemNameLabel = new QLabel("Item name:");
    QLabel *itemTypeLabel = new QLabel("Item type:");
    QLabel *chartPositionLabel = new QLabel("Chart position:");

    QComboBox *itemNameComboBox = new QComboBox();
    itemNameComboBox->addItems(mItemNameStringList);

    QComboBox *itemTypeComboBox = new QComboBox();
    itemTypeComboBox->addItem("Input");
    itemTypeComboBox->addItem("Output");

    QComboBox *chartPositionComboBox = new QComboBox();
    for(int i = 0; i < TABWIDGETS_MAX; i++)
    {
        chartPositionComboBox->addItem(QString().number(i+1));
    }

    QPushButton *okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(released()), this, SLOT(on_signalNewChartOkButton_released()));

    QPushButton *cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(released()), this, SLOT(on_signalNewChartCancelButton_released()));

    horizontalLayout1->setAlignment(Qt::AlignCenter);
    horizontalLayout1->addWidget(itemNameLabel);
    horizontalLayout1->addWidget(itemNameComboBox);

    horizontalLayout2->setAlignment(Qt::AlignCenter);
    horizontalLayout2->addWidget(itemTypeLabel);
    horizontalLayout2->addWidget(itemTypeComboBox);

    horizontalLayout3->setAlignment(Qt::AlignCenter);
    horizontalLayout3->addWidget(chartPositionLabel);
    horizontalLayout3->addWidget(chartPositionComboBox);

    horizontalLayout4->setAlignment(Qt::AlignRight);
    horizontalLayout4->addWidget(okButton);
    horizontalLayout4->addWidget(cancelButton);

    verticalLayout->addLayout(horizontalLayout1);
    verticalLayout->addLayout(horizontalLayout2);
    verticalLayout->addLayout(horizontalLayout3);
    verticalLayout->addLayout(horizontalLayout4);

    mNewChartDialog->show();
    mNewChartDialog->exec();

    if(mNewChartOkButton_released && !itemNameComboBox->currentText().isEmpty())
    {
        mNewChartOkButton_released = false;

        Product::ProductType productType = Product::Input;
        if(itemTypeComboBox->currentText() == "Input")
        {
            productType = Product::Input;
        }
        else if(itemTypeComboBox->currentText() == "Output")
        {
            productType = Product::Output;
        }

        createChart(itemNameComboBox->currentText(), mTabWidgets[chartPositionComboBox->currentIndex()], productType);
    }

    delete mNewChartDialog;
}


/*************************************************************************
 * SLOT ACTIONS
 *************************************************************************/
void MainWindow::on_signalPeriodicReadTimer_timeout(void)
{
    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    populateItemList();
    updateCharts();
}

void MainWindow::on_signalNewChartOkButton_released(void)
{
    mNewChartOkButton_released = true;

    mNewChartDialog->close();
}

void MainWindow::on_signalNewChartCancelButton_released(void)
{
    mNewChartDialog->close();
}

void MainWindow::on_signalTabWidget_tabCloseRequested_0(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[0]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_1(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[1]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_2(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[2]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_3(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[3]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_4(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[4]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_5(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[5]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_6(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[6]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_7(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[7]);
}
void MainWindow::on_signalTabWidget_tabCloseRequested_8(int index)
{
    on_signalTabWidget_tabCloseRequested(index, mTabWidgets[8]);
}

void MainWindow::on_signalTabWidget_tabCloseRequested(int index, QTabWidget *tabWidget)
{
    tabWidget->removeTab(index);
    if(tabWidget->currentIndex() == -1)
    {
        tabWidget->hide();
    }
}

/*************************************************************************
 * MainWindow::createChart
 *************************************************************************/
void MainWindow::createChart(const QString &name, QTabWidget *tabWidget, Product::ProductType productType)
{
    /* Create ProductionGraph */
    ProductionGraph productionGraph;
    QString tabNameProductType;
    bool alreadyCreated = false;

    for(int i = 0; i < mProductionGraphs.count(); i++)
    {
        if(mProductionGraphs[i].product.getName() == name && mProductionGraphs[i].product.getProductType() == productType)
        {
            qDebug() << "Chart already created, reopening in new tab";
            productionGraph = mProductionGraphs[i];
            alreadyCreated = true;
            break;
        }
    }

    if(!alreadyCreated)
    {
        /* Initialize ProductionGraph */
        productionGraph.product.setName(name);
        productionGraph.product.setProductType(productType);
        productionGraph.x = 0;
        productionGraph.minValue = 999999999;
        productionGraph.maxValue = 0;
        productionGraph.prevValue = 0;
        productionGraph.firstTime = true;

        /* Create QChart */
        productionGraph.chart = new QtCharts::QChart();

        /* Create QChartView */
        productionGraph.chartView = new QtCharts::QChartView(productionGraph.chart, ui->centralWidget);

        /* Create QAxes */
        productionGraph.timestampAxisX = new QtCharts::QValueAxis;
        productionGraph.timestampAxisY = new QtCharts::QValueAxis;

        /* Create QLineSeries' */
        productionGraph.mainLineSeries = new QtCharts::QLineSeries();

        ProductionAnalyzerSeries productionAnalyzerSeries;
        productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
        productionAnalyzerSeries.numDataToAvg = 10;
        productionGraph.productionAnalyzerSeries.append(productionAnalyzerSeries);

        productionAnalyzerSeries.lineSeries = new QtCharts::QLineSeries();
        productionAnalyzerSeries.numDataToAvg = 15;
        productionGraph.productionAnalyzerSeries.append(productionAnalyzerSeries);

        /* Add QLineSeries' to QChart */
        productionGraph.chart->addSeries(productionGraph.mainLineSeries);
        for(int i = 0; i < productionGraph.productionAnalyzerSeries.count(); i++)
        {
            productionGraph.chart->addSeries(productionGraph.productionAnalyzerSeries[i].lineSeries);
        }

        /* Configure QChart */
        productionGraph.chart->setTitle(name);
        //productionGraph.chart->legend()->hide();

        /* Add QAxes to QChart */
        productionGraph.chart->addAxis(productionGraph.timestampAxisX, Qt::AlignBottom);
        productionGraph.chart->addAxis(productionGraph.timestampAxisY, Qt::AlignLeft);

        /* Attach QLineSeries' to QAxes */
        productionGraph.mainLineSeries->attachAxis(productionGraph.timestampAxisY);
        productionGraph.mainLineSeries->attachAxis(productionGraph.timestampAxisX);
        productionGraph.mainLineSeries->setName(name);
        for(int i = 0; i < productionGraph.productionAnalyzerSeries.count(); i++)
        {
            productionGraph.productionAnalyzerSeries[i].lineSeries->attachAxis(productionGraph.timestampAxisY);
            productionGraph.productionAnalyzerSeries[i].lineSeries->attachAxis(productionGraph.timestampAxisX);
            productionGraph.productionAnalyzerSeries[i].lineSeries->setName(name+"-avg-over-"+QString::number(productionGraph.productionAnalyzerSeries[i].numDataToAvg));
        }

        /* Configure QChartView */
        productionGraph.chartView->setRenderHint(QPainter::Antialiasing);
    }

    switch(productionGraph.product.getProductType())
    {
    case Product::Input:
        tabNameProductType = "-produced";
        break;
    case Product::Output:
        tabNameProductType = "-consumed";
        break;
    }

    /* Add a new tab to the QTabView where this will be placed */
    tabWidget->addTab(productionGraph.chartView, name+tabNameProductType);
    tabWidget->show();

    if(!alreadyCreated)
    {
        /* Add now fully configured ProductionAnalyzerGraphs to QVector */
        mProductionGraphs.append(productionGraph);
    }
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
    for(int i = 0; i < mProductionGraphs.size(); i++)
    {
        QVector<Product> products;
        switch(mProductionGraphs[i].product.getProductType())
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
            if(product.getName() == mProductionGraphs[i].product.getName())
            {
                /* Get the value */
                curValue = product.getValue();

                /* If this is the first data point read from the file... */
                if(mProductionGraphs[i].firstTime)
                {
                    /* Set the outValue (a change between readings) to 0 to avoid huge value from first reading of file */
                    outValue = 0;

                    mProductionGraphs[i].firstTime = false;
                }
                else
                {
                    /* Calculate the change from the previous count to now */
                    outValue = curValue - mProductionGraphs[i].prevValue;
                }

                /* Set the preValue to use for calculating the change on the next data reading */
                mProductionGraphs[i].prevValue = curValue;

                /* Expand the scale of the graph downward to fit the data if necessary */
                if(outValue < mProductionGraphs[i].minValue)
                {
                    mProductionGraphs[i].minValue = outValue;
                }

                /* Expand the scale of the graph upward to fit the data if necessary */
                if(outValue > mProductionGraphs[i].maxValue)
                {
                    mProductionGraphs[i].maxValue = outValue;
                }

                /* Append the data to the main lineSeries */
                mProductionGraphs[i].mainLineSeries->append(mProductionGraphs[i].x, outValue);
                if(mProductionGraphs[i].mainLineSeries->count() > PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
                {
                    mProductionGraphs[i].mainLineSeries->removePoints(mProductionGraphs[i].mainLineSeries->count() - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX, 1);
                }

                /* For each series on this ith graph */
                for(int j = 0; j < mProductionGraphs[i].productionAnalyzerSeries.count(); j++)
                {
                    /* Average most current values in line series to smooth things out */
                    int index_max = mProductionGraphs[i].mainLineSeries->count() - 1;
                    int avg_count = mProductionGraphs[i].productionAnalyzerSeries[j].numDataToAvg;
                    if(index_max > avg_count)
                    {
                        outValue = 0;
                        for(int k = index_max; k > index_max - avg_count; k--)
                        {
                            outValue += mProductionGraphs[i].mainLineSeries->at(k).y();
                        }
                        outValue /= avg_count;

                        mProductionGraphs[i].productionAnalyzerSeries[j].lineSeries->append(mProductionGraphs[i].x, outValue);
                        if(mProductionGraphs[i].productionAnalyzerSeries[j].lineSeries->count() > PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
                        {
                            mProductionGraphs[i].productionAnalyzerSeries[j].lineSeries->removePoints(mProductionGraphs[i].productionAnalyzerSeries[j].lineSeries->count() - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX, 1);
                        }
                    }
                }
            }
        }

        /* Set min/max values for axes using the values saved above */
        mProductionGraphs[i].timestampAxisY->setMax(mProductionGraphs[i].maxValue);
        mProductionGraphs[i].timestampAxisY->setMin(mProductionGraphs[i].minValue);

        /* Set max x if the x value is larger than the current max */
        if(mProductionGraphs[i].x > mProductionGraphs[i].timestampAxisX->max())
        {
            mProductionGraphs[i].timestampAxisX->setMax(mProductionGraphs[i].x);

            /* Set the min higher to keep it "scrolling" once it fills the time span */
            if(mProductionGraphs[i].x >= PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX)
            {
                mProductionGraphs[i].timestampAxisX->setMin(mProductionGraphs[i].x - PRODUCTION_DATA_BUFFER_SIZE_OBJECTS_MAX + 1);
            }
        }

        /* Increment x for the next go around */
        mProductionGraphs[i].x = mProductionGraphs[i].x + 1;
    }
}

void MainWindow::populateItemList()
{
    QVector<Product> newInputs;
    QVector<Product> newOutputs;

    /* Get the latest production inputs */
    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();

    /* Look through the products available in the file */
    foreach (const Product &product, newInputs)
    {
        QString name = product.getName();
        if(!mItemNameStringList.contains(name))
        {
            mItemNameStringList.append(name);
        }
    }

    /* Get the latest production inputs */
    newOutputs = mProductionAnalyzer.getProductionData().last().getOutputs();

    /* Look through the products available in the file */
    foreach (const Product &product, newOutputs)
    {
        QString name = product.getName();
        if(!mItemNameStringList.contains(name))
        {
            mItemNameStringList.append(name);
        }
    }

    mItemNameStringList.sort();
}

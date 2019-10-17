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

/*************************************************************************
 * MainWindow::MainWindow
 *************************************************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /* Setup Qt Designer part of the UI */
    ui->setupUi(this);

    /* Create a timer to use for periodic reading of the Factorio mod output data file */
    periodicReadTimer = new QTimer(this);
    connect(periodicReadTimer, SIGNAL(timeout()), this, SLOT(periodicReadTimer_timeout()));

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
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_0(int)));
            break;

        case 1:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_1(int)));
            break;

        case 2:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_2(int)));
            break;

        case 3:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_3(int)));
            break;

        case 4:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_4(int)));
            break;

        case 5:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_5(int)));
            break;

        case 6:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_6(int)));
            break;

        case 7:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_7(int)));
            break;

        case 8:
            connect(mTabWidgets[i], SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidget_tabCloseRequested_8(int)));
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

/*************************************************************************
 * MainWindow::~MainWindow
 *************************************************************************/
MainWindow::~MainWindow()
{
    delete periodicReadTimer;
    delete ui;
}

/*************************************************************************
 * MENU ACTIONS
 *************************************************************************/
/*************************************************************************
 * MainWindow::on_actionOpen_triggered
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

/*************************************************************************
 * MainWindow::on_actionNewChart_triggered
 *************************************************************************/
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
    connect(okButton, SIGNAL(released()), this, SLOT(newChartOkButton_released()));

    QPushButton *cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(released()), this, SLOT(newChartCancelButton_released()));

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
/*************************************************************************
 * MainWindow::periodicReadTimer_timeout
 *************************************************************************/
void MainWindow::periodicReadTimer_timeout(void)
{
#if DEBUG_MAIN_WINDOW
    qDebug("MainWindow::periodicRead");
#endif
    mProductionAnalyzer.fileRead();

    populateItemList();
    updateCharts();
}

/*************************************************************************
 * MainWindow::newChartOkButton_released
 *************************************************************************/
void MainWindow::newChartOkButton_released(void)
{
    mNewChartOkButton_released = true;

    mNewChartDialog->close();
}

/*************************************************************************
 * MainWindow::newChartCancelButton_released
 *************************************************************************/
void MainWindow::newChartCancelButton_released(void)
{
    mNewChartDialog->close();
}

/*************************************************************************
 * MainWindow::tabWidget_tabCloseRequested_X
 *************************************************************************/
void MainWindow::tabWidget_tabCloseRequested_0(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[0]);
}
void MainWindow::tabWidget_tabCloseRequested_1(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[1]);
}
void MainWindow::tabWidget_tabCloseRequested_2(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[2]);
}
void MainWindow::tabWidget_tabCloseRequested_3(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[3]);
}
void MainWindow::tabWidget_tabCloseRequested_4(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[4]);
}
void MainWindow::tabWidget_tabCloseRequested_5(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[5]);
}
void MainWindow::tabWidget_tabCloseRequested_6(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[6]);
}
void MainWindow::tabWidget_tabCloseRequested_7(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[7]);
}
void MainWindow::tabWidget_tabCloseRequested_8(int index)
{
    tabWidget_tabCloseRequested(index, mTabWidgets[8]);
}

/*************************************************************************
 * MainWindow::tabWidget_tabCloseRequested
 *************************************************************************/
void MainWindow::tabWidget_tabCloseRequested(int index, QTabWidget *tabWidget)
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
    ProductionGraph *productionGraph = nullptr;
    QString tabNameProductType;
    bool alreadyCreated = false;

    for(int i = 0; i < mProductionGraphs.count(); i++)
    {
        if(mProductionGraphs[i]->getProduct().getName() == name && mProductionGraphs[i]->getProduct().getProductType() == productType)
        {
            qDebug() << "Chart already created, reopening in new tab";
            productionGraph = mProductionGraphs[i];
            alreadyCreated = true;
            break;
        }
    }

    if(!alreadyCreated)
    {
        productionGraph = new ProductionGraph(productType, ui->centralWidget, name);
    }

    if(productionGraph != nullptr)
    {
        switch(productionGraph->getProduct().getProductType())
        {
        case Product::Input:
            tabNameProductType = "-produced";
            break;
        case Product::Output:
            tabNameProductType = "-consumed";
            break;
        }

        /* Add a new tab to the QTabView where this will be placed */
        tabWidget->addTab(productionGraph->getChartView(), name+tabNameProductType);
        tabWidget->show();

        if(!alreadyCreated)
        {
            /* Add now fully configured ProductionAnalyzerGraphs to QVector */
            mProductionGraphs.append(productionGraph);
        }
    }
}

/*************************************************************************
 * MainWindow::updateCharts
 *************************************************************************/
void MainWindow::updateCharts()
{
    QVector<Product> newInputs;
    QVector<Product> newOutputs;

    /* Get the latest production inputs */
    newInputs = mProductionAnalyzer.getProductionData().last().getInputs();

    /* Get the latest production inputs */
    newOutputs = mProductionAnalyzer.getProductionData().last().getOutputs();

    /* Loop through and update each graph */
    for(int i = 0; i < mProductionGraphs.size(); i++)
    {
        QVector<Product> products;

        /* Determine the graph's product's productType (input vs output) */
        switch(mProductionGraphs[i]->getProduct().getProductType())
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
            if(product.getName() == mProductionGraphs[i]->getProduct().getName())
            {
                /* If we find the data then we update the graph */
                mProductionGraphs[i]->setProduct(product);
                mProductionGraphs[i]->update();
            }
        }
    }
}

/*************************************************************************
 * MainWindow::populateItemList
 *************************************************************************/
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

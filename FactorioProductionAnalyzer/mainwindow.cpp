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
    QString fileDialogPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.factorio/script-output/FactorioProductionAnalyzer/production_data.json";
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
            periodicReadTimer->start(1000);
        }
        else if(fileName.contains(".dat"))
        {
            mProductionAnalyzer.setFile(ProductionAnalyzer::Binary, fileName);
            periodicReadTimer->start(1000);
        }
    }
}

/*************************************************************************
 * SLOT ACTIONS
 *************************************************************************/
void MainWindow::periodicRead(void)
{
    qDebug("MainWindow::periodicRead");
    mProductionAnalyzer.fileRead();

    int timestamp = mProductionAnalyzer.getProductionData().getTimestamp();
    ui->lcdNumber->display(timestamp);
}

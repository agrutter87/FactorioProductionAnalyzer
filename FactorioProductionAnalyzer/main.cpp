#include "mainwindow.h"
#include <QApplication>

#include "productionanalyzer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ProductionAnalyzer productionAnalyzer;
    productionAnalyzer.fileRead(ProductionAnalyzer::Json);

    ProductionData productionData;
    productionData = productionAnalyzer.getProductionData();

    return a.exec();
}

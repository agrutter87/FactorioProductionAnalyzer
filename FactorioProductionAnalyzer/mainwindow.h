#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QHBoxLayout>
#include <QDialog>

#include "productionanalyzer.h"

#define NUM_CHARTS_PER_ROW  (3)
#define HBOXLAYOUTS_MAX     (3)
#define TABWIDGETS_MAX      (9)
#if (TABWIDGETS_MAX % HBOXLAYOUTS_MAX != 0)
#error "TABWIDGETS_MAX must be divisible by HBOXLAYOUTS_MAX"
#else
#define VBOXLAYOUT_ROWS     (TABWIDGETS_MAX / HBOXLAYOUTS_MAX)
#endif

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef struct
    {
        QtCharts::QLineSeries *lineSeries;
        int numDataToAvg;
    } ProductionAnalyzerSeries;

    typedef struct
    {
        QtCharts::QChart *chart;
        QtCharts::QChartView *chartView;
        QtCharts::QValueAxis *timestampAxisX;
        QtCharts::QValueAxis *timestampAxisY;
        QtCharts::QLineSeries *mainLineSeries;
        QVector<ProductionAnalyzerSeries> productionAnalyzerSeries;
        Product product;
        qreal x;
        qreal minValue;
        qreal maxValue;
        qreal prevValue;
        bool firstTime;
    } ProductionAnalyzerGraph;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createChart(const QString &name, QTabWidget *tabWidget, Product::ProductType productType);
    void updateCharts();
    void populateItemList();

private slots:
    void on_actionOpen_triggered();
    void on_actionNewChart_triggered();

    void on_signalPeriodicReadTimer_timeout();
    void on_signalNewChartOkButton_released();
    void on_signalNewChartCancelButton_released();

private:
    Ui::MainWindow *ui;
    ProductionAnalyzer mProductionAnalyzer;
    QTimer *periodicReadTimer;
    QVector<ProductionAnalyzerGraph> mProductionAnalyzerGraphs;

    QTabWidget *mTabWidgets[TABWIDGETS_MAX];
    QHBoxLayout *mHBoxLayouts[HBOXLAYOUTS_MAX];

    QDialog *mNewChartDialog;
    QStringList mItemNameStringList;
    bool mNewChartOkButton_released;
};

#endif // MAINWINDOW_H

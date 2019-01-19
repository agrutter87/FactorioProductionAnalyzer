#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>

#include "productionanalyzer.h"

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
        QtCharts::QChart *chart;
        QtCharts::QChartView *chartView;
        QtCharts::QValueAxis *timestampAxisX;
        QtCharts::QValueAxis *timestampAxisY;
        QtCharts::QLineSeries *lineSeries;
        Product product;
        qreal x;
        qreal minValue;
        qreal maxValue;
        qreal prevValue;
        bool firstTime;
    } ProductionAnalyzerGraph;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createChart(const QString &name);
    void updateCharts();

private slots:
    void on_actionOpen_triggered();
    void periodicRead(void);

private:
    Ui::MainWindow *ui;
    ProductionAnalyzer mProductionAnalyzer;
    QTimer *periodicReadTimer;

    QVector<ProductionAnalyzerGraph> mProductionAnalyzerGraphs;
};

#endif // MAINWINDOW_H

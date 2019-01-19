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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createChart();
    void updateChart();

private slots:
    void on_actionOpen_triggered();
    void periodicRead(void);

private:
    Ui::MainWindow *ui;
    ProductionAnalyzer mProductionAnalyzer;
    QTimer *periodicReadTimer;

    QtCharts::QChart *mChart;
    QtCharts::QChartView *mChartView;
    QtCharts::QValueAxis *mTimestampAxisX;
    QtCharts::QValueAxis *mTimestampAxisY;

    QtCharts::QLineSeries *mLineSeries;
    QtCharts::QLineSeries *mLineSeries2;
};

#endif // MAINWINDOW_H

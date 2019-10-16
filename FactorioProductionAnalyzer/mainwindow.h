#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QDialog>

#include "productionanalyzer.h"
#include "productiongraph.h"

#define NUM_CHARTS_PER_ROW  (3)
#define HBOXLAYOUTS_MAX     (3)
#define TABWIDGETS_MAX      (9)

#if (TABWIDGETS_MAX % HBOXLAYOUTS_MAX != 0)
#error "TABWIDGETS_MAX must be divisible by HBOXLAYOUTS_MAX"
#else
#define VBOXLAYOUT_ROWS     (TABWIDGETS_MAX / HBOXLAYOUTS_MAX)
#endif

#if (TABWIDGETS_MAX > 9)
#error "Define more on_signalTabWidget_tabCloseRequested functions to add more QTabWidgets!"
#endif

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

    void createChart(const QString &name, QTabWidget *tabWidget, Product::ProductType productType);
    void updateCharts();
    void populateItemList();

private slots:
    void on_actionOpen_triggered();
    void on_actionNewChart_triggered();

    void on_signalPeriodicReadTimer_timeout();
    void on_signalNewChartOkButton_released();
    void on_signalNewChartCancelButton_released();
    void on_signalTabWidget_tabCloseRequested_0(int index);
    void on_signalTabWidget_tabCloseRequested_1(int index);
    void on_signalTabWidget_tabCloseRequested_2(int index);
    void on_signalTabWidget_tabCloseRequested_3(int index);
    void on_signalTabWidget_tabCloseRequested_4(int index);
    void on_signalTabWidget_tabCloseRequested_5(int index);
    void on_signalTabWidget_tabCloseRequested_6(int index);
    void on_signalTabWidget_tabCloseRequested_7(int index);
    void on_signalTabWidget_tabCloseRequested_8(int index);
    void on_signalTabWidget_tabCloseRequested(int index, QTabWidget *tabWidget);

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

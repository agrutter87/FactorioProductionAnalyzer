#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QDialog>

#include "productionanalyzer.h"
#include "productioncalculator.h"
#include "productiongraph.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define NUM_CHARTS_PER_ROW              (3)
#define HBOXLAYOUTS_MAX                 (3)
#define TABWIDGETS_MAX                  (9)

#if (TABWIDGETS_MAX % HBOXLAYOUTS_MAX != 0)
#error "TABWIDGETS_MAX must be divisible by HBOXLAYOUTS_MAX"
#else
#define VBOXLAYOUT_ROWS                 (TABWIDGETS_MAX / HBOXLAYOUTS_MAX)
#endif

#if (TABWIDGETS_MAX > 9)
#error "Define more tabWidget_tabCloseRequested functions to add more QTabWidgets!"
#endif

#define DEBUG_MAIN_WINDOW               (0)

/*************************************************************************
 * Ui Namespace
 *************************************************************************/
namespace Ui
{
    class MainWindow;
}

/*************************************************************************
 * MainWindow Class
 *************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit                            MainWindow(QWidget *parent = nullptr);
                                        ~MainWindow();

    void                                createChart(const QString &name, QTabWidget *tabWidget, Product::ProductType productType);
    void                                updateCharts();
    void                                populateItemList();

private slots:
    void                                on_actionOpen_triggered();
    void                                on_actionNewChart_triggered();
    void                                on_actionCalculator_triggered();

    void                                periodicReadTimer_timeout();
    void                                newChartOkButton_clicked();
    void                                newChartCancelButton_clicked();
    void                                tabWidget_tabCloseRequested_0(int index);
    void                                tabWidget_tabCloseRequested_1(int index);
    void                                tabWidget_tabCloseRequested_2(int index);
    void                                tabWidget_tabCloseRequested_3(int index);
    void                                tabWidget_tabCloseRequested_4(int index);
    void                                tabWidget_tabCloseRequested_5(int index);
    void                                tabWidget_tabCloseRequested_6(int index);
    void                                tabWidget_tabCloseRequested_7(int index);
    void                                tabWidget_tabCloseRequested_8(int index);
    void                                tabWidget_tabCloseRequested(int index, QTabWidget *tabWidget);

private:
    Ui::MainWindow                      *ui;
    ProductionAnalyzer                  mProductionAnalyzer;
    ProductionCalculator                *mProductionCalculator;
    QTimer                              *periodicReadTimer;
    QVector<ProductionGraph*>           mProductionGraphs;

    QTabWidget                          *mTabWidgets[TABWIDGETS_MAX];
    QHBoxLayout                         *mHBoxLayouts[HBOXLAYOUTS_MAX];

    QDialog                             *mNewChartDialog;
    QStringList                         mItemNameStringList;
    bool                                mNewChartOkButton_clicked;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_actionOpen_triggered();
    void periodicRead(void);

private:
    Ui::MainWindow *ui;
    ProductionAnalyzer mProductionAnalyzer;
    QTimer *periodicReadTimer;
};

#endif // MAINWINDOW_H

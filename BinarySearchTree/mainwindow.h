#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "renderarea.h"
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    RenderArea *renderArea;
};

#endif // MAINWINDOW_H

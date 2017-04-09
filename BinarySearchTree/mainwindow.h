#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include "renderarea.h"
#include "bst_properties_window.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea *renderArea;
    BST_Properties_Window *prop;
    QMenuBar *menuBar;

protected:
    virtual void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

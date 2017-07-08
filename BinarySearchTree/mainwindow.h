#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include "renderarea.h"
/*
 * bst_properties_window.h includes:
 * QMainWindow, QVBoxLayout, QHBoxLayout, QScrollArea, QWidget, QLabel, QLineEdit
 */
#include "bst_properties_window.h"
#include "binarysearchtree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    RenderArea *renderArea;
    QPushButton *propertyButton;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QLineEdit *insertValueLineEdit;
    QScrollArea *treeScrollArea;
    BST_Properties_Window *prop;
    BinarySearchTree<int> *bst;
    BinarySearchTree<int> *getBST();
    void buildMenu();

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void propertyClicked() const;
    void insertClicked() const;
    void deleteClicked() const;
    void zoomInClicked() const;
    void zoomOutClicked() const;
};

#endif // MAINWINDOW_H

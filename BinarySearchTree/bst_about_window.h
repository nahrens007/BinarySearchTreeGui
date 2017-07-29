/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 */

#ifndef BST_ABOUT_WINDOW_H
#define BST_ABOUT_WINDOW_H

#include "binarysearchtree.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class BST_About_Window
{
public:
    BST_About_Window();
    ~BST_About_Window();
    void show();
    void close();

private:
    QMainWindow *window;
    QVBoxLayout *labelLayout;
    QHBoxLayout *containerLayout;
    QWidget *container;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;
};

#endif // BST_ABOUT_WINDOW_H

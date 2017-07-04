#ifndef BST_PROPERTIES_WINDOW_H
#define BST_PROPERTIES_WINDOW_H

#include "binarysearchtree.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>

class BST_Properties_Window
{
public:
    BST_Properties_Window();
    ~BST_Properties_Window();
    void requestFocus() const;
    void create();
    void close() const;
    void update(BinarySearchTree<int> *bst);

private:
    QMainWindow *window;
    QVBoxLayout *labelLayout;
    QLabel *heightLabel;
    QLabel *heightLabelValue;
    QVBoxLayout *textAreaLayout;
    QHBoxLayout *containerLayout;
    QWidget *container;
    QScrollArea *scrollArea;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;
};

#endif // BST_PROPERTIES_WINDOW_H

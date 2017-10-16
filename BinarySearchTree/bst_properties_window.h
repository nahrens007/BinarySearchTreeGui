/*
 * Binary Search Tree Visualization
 * Ashland University
 * Nathan Ahrens
 * Summer 2017
 */

#ifndef BST_PROPERTIES_WINDOW_H
#define BST_PROPERTIES_WINDOW_H

#include "binarysearchtree.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class BST_Properties_Window : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;
public:
    explicit BST_Properties_Window(QWidget *parent = 0);
    ~BST_Properties_Window();
    void show();
    void closePropertyWindow();
    void update(BinarySearchTree<int> *bst);

private:
    QVBoxLayout *labelLayout;
    QLabel *heightLabel;
    QLineEdit *heightValue;
    QLabel *nodeCountLabel;
    QLineEdit *nodeCountValue;
    QLabel *leafNodesLabel;
    QLineEdit *leafNodesValue;
    QLabel *internalNodesLabel;
    QLineEdit *internalNodesValue;
    QVBoxLayout *textAreaLayout;
    QHBoxLayout *containerLayout;
    QVBoxLayout *mainLayout;
    QTextEdit *inOrderTraversal;
    QTextEdit *preOrderTraversal;
    QTextEdit *postOrderTraversal;
    QTextEdit *breadthFirstTraversal;
    QPushButton *exitButton;

private slots:
    void exitSlot();
};

#endif // BST_PROPERTIES_WINDOW_H

#ifndef BST_PROPERTIES_WINDOW_H
#define BST_PROPERTIES_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class BST_Properties_Window
{
public:
    BST_Properties_Window();
    ~BST_Properties_Window();
    void requestFocus() const;
    void create();
    void close() const;

private:
    QMainWindow *window;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *widget;
    void update();
};

#endif // BST_PROPERTIES_WINDOW_H

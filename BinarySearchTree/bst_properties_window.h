#ifndef BST_PROPERTIES_WINDOW_H
#define BST_PROPERTIES_WINDOW_H

#include <QMainWindow>

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
    void update();
};

#endif // BST_PROPERTIES_WINDOW_H

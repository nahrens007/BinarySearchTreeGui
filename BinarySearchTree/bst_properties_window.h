#ifndef BST_PROPERTIES_WINDOW_H
#define BST_PROPERTIES_WINDOW_H

#include <QWindow>


class BST_Properties_Window
{
public:
    BST_Properties_Window();
    ~BST_Properties_Window();
    void requestFocus() const;
    void create() const;
    void close() const;

private:
    QWindow *window;
    void update();
};

#endif // BST_PROPERTIES_WINDOW_H

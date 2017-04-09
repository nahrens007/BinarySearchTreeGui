#include "bst_properties_window.h"

BST_Properties_Window::BST_Properties_Window()
{
    window = new QWindow();
    window->setTitle("Properties");
    window->setMinimumSize(QSize(300, 200));
}
BST_Properties_Window::~BST_Properties_Window(){
    delete window;
}

void BST_Properties_Window::close() const{
    window->destroy();
}

void BST_Properties_Window::update() {
    // update the properties of the tree
}

// bring the window to the front.
void BST_Properties_Window::requestFocus() const{
    window->requestActivate();
}

// create the window and display it.
void BST_Properties_Window::create() const{
    window->create();
    window->setVisible(true);
    window->requestActivate();
}

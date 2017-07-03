#include "bst_properties_window.h"
#include <QLabel>
#include <QVBoxLayout>

BST_Properties_Window::BST_Properties_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("Properties");
    window->setMinimumSize(QSize(300, 200));    
}
BST_Properties_Window::~BST_Properties_Window(){
    delete window;
}

void BST_Properties_Window::close() const{
    window->close();
}

void BST_Properties_Window::update() {
    // update the properties of the tree
}

// bring the window to the front.
void BST_Properties_Window::requestFocus() const{
    window->activateWindow();
}

// create the window and display it.
void BST_Properties_Window::create(){
    window->activateWindow();
    window->setVisible(true);

    QLabel *label = new QLabel("Hello World");


    QVBoxLayout *labelLayout = new QVBoxLayout();
    labelLayout->addWidget(label);


    scrollArea = new QScrollArea();
    scrollArea->setLayout(labelLayout);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);

    window->setLayout(mainLayout);

}

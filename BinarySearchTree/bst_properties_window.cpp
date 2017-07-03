#include "bst_properties_window.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <iostream>

BST_Properties_Window::BST_Properties_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("Properties");
    window->setMinimumSize(QSize(300, 200));    
    std::cout << "Properties constructor" << std::endl;
}
BST_Properties_Window::~BST_Properties_Window(){
    delete window;
    std::cout << "Properties destructor" << std::endl;
}

void BST_Properties_Window::close() const{
    window->close();
    std::cout << "Properties close()" << std::endl;
}

void BST_Properties_Window::update() {
    // update the properties of the tree
    std::cout << "Properties update()" << std::endl;
}

// bring the window to the front.
void BST_Properties_Window::requestFocus() const{
    window->activateWindow();
    std::cout << "Properties requestFocus()" << std::endl;
}

// create the window and display it.
void BST_Properties_Window::create(){
    std::cout << "Properties create()" << std::endl;
    window->activateWindow();
    window->setVisible(true);

    QVBoxLayout *labelLayout = new QVBoxLayout;\
    for (int i = 0; i < 10; i++)
    {
        QLabel *newLabel = new QLabel("Hello World!!");
        labelLayout->addWidget(newLabel);
    }

    QWidget *container = new QWidget;
    container->setLayout(labelLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(container);

    // Create the main layout and add all the widgets to it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scrollArea);
    // mainLayout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(window);
    centralWidget->setLayout(mainLayout);

    window->setCentralWidget(centralWidget);

}

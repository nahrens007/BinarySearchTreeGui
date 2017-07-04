#include "bst_properties_window.h"
#include <iostream>

BST_Properties_Window::BST_Properties_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("Properties");
    window->setMinimumSize(QSize(300, 200));    
    std::cout << "Properties constructor" << std::endl;
}
BST_Properties_Window::~BST_Properties_Window(){
    delete heightLabel;
    delete heightLabelValue;
    delete labelLayout;
    delete textAreaLayout;
    delete containerLayout;
    delete container;
    delete scrollArea;
    delete mainLayout;
    delete centralWidget;
    delete window;
    std::cout << "Properties destructor" << std::endl;
}

void BST_Properties_Window::close() const{
    window->close();
    std::cout << "Properties close()" << std::endl;
}

void BST_Properties_Window::update(BinarySearchTree<int> *bst) {
    // update the properties of the tree
    std::cout << "Properties update()" << std::endl;
    std::cout<< "update() height: " << bst->getTreeHeight() << std::endl;
    this->heightLabelValue->setText(QString::number(bst->getTreeHeight()));
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

    // Create the label layout and labels, and add them all to it
    labelLayout = new QVBoxLayout;\
    heightLabel = new QLabel("Height:");
    labelLayout->addWidget(heightLabel);

    textAreaLayout = new QVBoxLayout;
    heightLabelValue = new QLabel("");
    textAreaLayout->addWidget(heightLabelValue);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(labelLayout);
    containerLayout->addLayout(textAreaLayout);

    container = new QWidget;
    container->setLayout(containerLayout);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(container);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scrollArea);
    // mainLayout->addLayout(buttonLayout); // layout for ok/close button

    centralWidget = new QWidget(window);
    centralWidget->setLayout(mainLayout);

    window->setCentralWidget(centralWidget);

}

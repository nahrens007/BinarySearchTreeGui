#include "bst_properties_window.h"
#include <iostream>

BST_Properties_Window::BST_Properties_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("Properties");
    window->setMinimumSize(QSize(300, 200));

    // labelLayout is on the left side - says what the property is
    labelLayout = new QVBoxLayout;\
    heightLabel = new QLabel("Height:");
    labelLayout->addWidget(heightLabel);

    // textAreaLayout is on the right side - displays value of property
    textAreaLayout = new QVBoxLayout;
    heightValue = new QLineEdit("");
    heightValue->setDisabled(true);
    heightValue->setStyleSheet("background-color: black; color: white;");
    textAreaLayout->addWidget(heightValue);

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

BST_Properties_Window::~BST_Properties_Window(){
    delete heightLabel;
    delete heightValue;
    delete labelLayout;
    delete textAreaLayout;
    delete containerLayout;
    delete container;
    delete scrollArea;
    delete mainLayout;
    delete centralWidget;
    delete window;
}

// Close the window.
void BST_Properties_Window::close() const{
    window->close();
}

// Update the properties of the tree.
void BST_Properties_Window::update(BinarySearchTree<int> *bst) {
    this->heightValue->setText(QString::number(bst->getTreeHeight()));
}

// Bring the window to the front.
void BST_Properties_Window::requestFocus() const
{
    window->activateWindow();
    return;
}

// Set window to visible and bring it to the front.
void BST_Properties_Window::create()
{
    window->setVisible(true);
    window->activateWindow();
    return;
}

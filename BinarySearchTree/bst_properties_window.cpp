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
    nodeCountLabel = new QLabel("Node count:");
    leafNodesLabel = new QLabel("Leaf nodes:");
    heightLabel->setStyleSheet("font-size: 14px;");
    nodeCountLabel->setStyleSheet("font-size: 14px;");
    leafNodesLabel->setStyleSheet("font-size: 14px;");

    labelLayout->addWidget(heightLabel);
    labelLayout->addWidget(nodeCountLabel);
    labelLayout->addWidget(leafNodesLabel);

    // textAreaLayout is on the right side - displays value of property
    textAreaLayout = new QVBoxLayout;
    heightValue = new QLineEdit("");
    nodeCountValue = new QLineEdit("");
    leafNodesValue = new QLineEdit("");
    heightValue->setDisabled(true);
    nodeCountValue->setDisabled(true);
    leafNodesValue->setDisabled(true);
    heightValue->setStyleSheet("background-color: black; color: white; "
                               "padding-left: 10px; font-size: 14px;");
    nodeCountValue->setStyleSheet("background-color: black; color: white; "
                                  "padding-left: 10px; font-size: 14px;");
    leafNodesValue->setStyleSheet("background-color: black; color: white; "
                                  "padding-left: 10px; font-size: 14px;");

    textAreaLayout->addWidget(heightValue);
    textAreaLayout->addWidget(nodeCountValue);
    textAreaLayout->addWidget(leafNodesValue);

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
    delete nodeCountLabel;
    delete nodeCountValue;
    delete leafNodesLabel;
    delete leafNodesValue;
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
    this->nodeCountValue->setText(QString::number(bst->getNodeCount()));
    this->leafNodesValue->setText(QString::number(bst->getLeafNodeCount()));
    return;
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

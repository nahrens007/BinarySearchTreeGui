#include "bst_properties_window.h"
#include <iostream>
#include <QScrollArea>

BST_Properties_Window::BST_Properties_Window()
{
    window = new QMainWindow();
    window->setWindowTitle("Properties");
    window->setFixedSize(QSize(400, 400)); // 236 width

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
    heightValue->setReadOnly(true);
    nodeCountValue->setReadOnly(true);
    leafNodesValue->setReadOnly(true);

    heightValue->setStyleSheet("color: black; width: 100px;"
                               "padding-left: 10px; font-size: 14px;");
    nodeCountValue->setStyleSheet("color: black; width: 100px;"
                                  "padding-left: 10px; font-size: 14px;");
    leafNodesValue->setStyleSheet("color: black; width: 100px;"
                                  "padding-left: 10px; font-size: 14px;");

    textAreaLayout->addWidget(heightValue);
    textAreaLayout->addWidget(nodeCountValue);
    textAreaLayout->addWidget(leafNodesValue);

    containerLayout = new QHBoxLayout;
    containerLayout->addLayout(labelLayout);
    containerLayout->addLayout(textAreaLayout);


    preOrderTraversal = new QTextEdit;
    inOrderTraversal = new QTextEdit;
    postOrderTraversal = new QTextEdit;
    preOrderTraversal->setReadOnly(true);
    inOrderTraversal->setReadOnly(true);
    postOrderTraversal->setReadOnly(true);

    // Create the main layout and add all the widgets to it
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(containerLayout);
    mainLayout->addWidget(new QLabel("Preorder Traversal:"));
    mainLayout->addWidget(preOrderTraversal);
    mainLayout->addWidget(new QLabel("Inorder Traversal:"));
    mainLayout->addWidget(inOrderTraversal);
    mainLayout->addWidget(new QLabel("Postorder Traversal:"));
    mainLayout->addWidget(postOrderTraversal);
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
    delete mainLayout;
    delete centralWidget;
    delete window;
}

// Close the window.
void BST_Properties_Window::close() const{
    window->close();
}

// Update the properties of the tree.
void BST_Properties_Window::update(BinarySearchTree<int> *bst)
{
    this->heightValue->setText(QString::number(bst->getTreeHeight()));
    this->nodeCountValue->setText(QString::number(bst->getNodeCount()));
    this->leafNodesValue->setText(QString::number(bst->getLeafNodeCount()));
    this->preOrderTraversal->setText(bst->getPreOrderTraversal());
    this->inOrderTraversal->setText(bst->getInOrderTraversal());
    this->postOrderTraversal->setText(bst->getPostOrderTraversal());
    return;
}

// Bring the window to the front.
void BST_Properties_Window::requestFocus() const
{
    window->activateWindow();
    return;
}

// Set window to visible and bring it to the front.
void BST_Properties_Window::show()
{
    window->setVisible(true);
    window->activateWindow();
    return;
}

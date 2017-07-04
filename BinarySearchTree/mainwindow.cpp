#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->bst = this->getBST();

    // Build buttons and layout for buttons on the bottom of the window
    propertyButton = new QPushButton("&Properties", this);
    deleteButton = new QPushButton("&Delete", this);
    insertButton = new QPushButton("&Insert", this);
    zoomInButton = new QPushButton("Zoom &In", this);
    zoomOutButton = new QPushButton("Zoom &Out", this);

    // Set properties of buttons
    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomInButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomOutButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    deleteButton->setEnabled(false);
    insertButton->setEnabled(false);

    // Connect the slots to the button signals
    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInClicked()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutClicked()));

    // Create button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(insertButton);
    //  need to add text edit for value to insert
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);

    // Create the main layout and add all the widgets to it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumSize(600, 400);
    this->setWindowTitle(tr("Binary Search Tree Visualization"));
    this->showMaximized();

    // Create the properties window (but do not display it)
    prop = new BST_Properties_Window();

}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete propertyButton;
    delete deleteButton;
    delete insertButton;
    delete zoomInButton;
    delete zoomOutButton;
    delete treeScrollArea;
    delete prop;
    delete bst;
    delete centralWidget;
}

void MainWindow::closeEvent(QCloseEvent *event){
    prop->close();
    event->accept();
    return;
}

void MainWindow::propertyClicked() const {
    prop->create();
    prop->update(this->bst);
    return;
}

void MainWindow::deleteClicked() const {

}

void MainWindow::insertClicked() const {

}

void MainWindow::zoomInClicked() const {
    renderArea->zoomIn();
    return;
}

void MainWindow::zoomOutClicked() const {
    renderArea->zoomOut();
    return;
}

BinarySearchTree<int>* MainWindow::getBST()
{
    BinarySearchTree<int> *bst = new BinarySearchTree<int>;
    int height = -1;

    switch(height){
    case -1:{
        int arrayElements = 23;
        int custArray[arrayElements] = {100, 50, 25, 15, 20, 30, 27, 75, 150, 175, 160, 155, 165, 190, 180, 200, 5, 3, 4, 1, 2, 8, 6};

        for(int i = 0; i < arrayElements; i++)
            bst->insert(custArray[i]);
    }
        break;
    case 1:{
        int arr1[3] = {50, 30, 60};

        for(int i = 0; i < 3; i++)
            bst->insert(arr1[i]);
    }
        break;
    case 2:{
        int arr2[7] = {50, 30, 60, 25, 35, 55, 65};

        for(int i = 0; i < 7; i++)
            bst->insert(arr2[i]);
    }
        break;
    case 3:{
        int arr3[15] = {50, 30, 60, 25, 35, 55, 65, 20, 27, 33, 37, 53, 57, 63, 67};

        for(int i = 0; i < 15; i++)
            bst->insert(arr3[i]);
    }
        break;
    case 4: {
        int arr4[31] = {50, 30, 20, 15, 5, 17, 25, 23, 27, 40, 35, 33, 37, 45, 43, 47, 70, 60, 55, 53, 57, 65, 63, 67, 80, 75, 85, 73, 77, 83, 87};

        for(int i = 0; i < 31; i++)
            bst->insert(arr4[i]);
    }
        break;
    case 5:{
        int arr5[65] = {50, 30, 20, 15, 5, 17, 25, 23, 27, 40, 35, 33, 37, 45, 43, 47, 70, 60, 55, 53, 57, 65, 63, 67, 80, 75, 85, 73, 77, 83, 87, 1,
                      7, 16, 18, 22, 24, 26, 28, 32, 34, 36, 38, 42, 44, 46, 48, 52, 54, 56, 58, 62, 64, 66, 68, 72, 74, 76, 78, 82, 84, 82, 84, 86, 88};

        for(int i = 0; i < 65; i++)
            bst->insert(arr5[i]);
    }
        break;
    default:
        qsrand(QTime::currentTime().msec());
        for (int count = 0; count < 900; count++)
            bst->insert(qrand() % ((999 + 1) - 1) + 1);
    }

    return bst;
}

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

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
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea;

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
    delete prop;
    delete renderArea;
    delete centralWidget;

}

void MainWindow::closeEvent(QCloseEvent *event){
    prop->close();
    event->accept();
}

void MainWindow::propertyClicked() const {

    prop->create();
}

void MainWindow::deleteClicked() const {

}

void MainWindow::insertClicked() const {

}

void MainWindow::zoomInClicked() const {
    renderArea->zoomIn();
}

void MainWindow::zoomOutClicked() const {
    renderArea->zoomOut();
}

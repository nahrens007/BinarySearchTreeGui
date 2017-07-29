#include "mainwindow.h"
#include "bst_about_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStringListIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Create default save directory
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer";
    if (!QDir(directory).exists())
        QDir().mkdir(directory);

    this->bst = this->getBST();

    this->createMenu();

    // Build buttons and layout for buttons on the bottom of the window
    propertyButton = new QPushButton("&Properties", this);
    deleteButton = new QPushButton("&Delete", this);
    insertButton = new QPushButton("Insert", this);
    zoomInButton = new QPushButton("Zoom &In", this);
    zoomOutButton = new QPushButton("Zoom &Out", this);
    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;

    // Set properties of buttons
    propertyButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomInButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoomOutButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    insertValueLineEdit->setFixedWidth(200);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");

    deleteValueLineEdit->setFixedWidth(100);
    deleteValueLineEdit->setToolTip("Enter value to delete");

    // Connect the slots to the button signals
    connect(propertyButton, SIGNAL(clicked()), this, SLOT(propertyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomInClicked()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOutClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));

    // Create button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(propertyButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(25);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);

    // Create the render area (canvas for drawing the BST)
    renderArea = new RenderArea(this->bst);

    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);

    // Pass any events that happen on the scroll area to the
    // render area (specifically clicking, so that renderArea
    // can zoom in/out when clicks happen
    treeScrollArea->installEventFilter(renderArea);

    // Create the main layout and add all the widgets to it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);

    // Build the main window
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(400);
    this->setWindowTitle("Binary Search Tree Visualization");
    this->showMaximized();

    // Create secondary windows (but do not display them)
    prop = new BST_Properties_Window();
    about = new BST_About_Window();
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
    delete about;
    delete bst;
    delete centralWidget;
}

void MainWindow::createMenu()
{
    this->createActions();

    fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    editMenu = this->menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(resetAction);

    this->menuBar()->addAction(aboutAction);
}

void MainWindow::createActions()
{
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip("About Binary Search Tree Visualization");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutMenu);

    loadAction = new QAction(tr("&Load"), this);
    loadAction->setStatusTip("Load a BST from a file");
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadFileMenu);

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setStatusTip("Save a BST to a file");
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveMenu);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitMenu);

    resetAction = new QAction(tr("&Reset"), this);
    resetAction->setStatusTip("Reset the BST to be empty");
    connect(resetAction, &QAction::triggered, this, &MainWindow::resetMenu);

}

void MainWindow::closeEvent(QCloseEvent *event)
{

    // Save BST before closing
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QString text = bst->getPreOrderTraversal();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
    }

    prop->close(); // close property window
    about->close(); // close about window
    event->setAccepted(true); // set whether to close application or not
    return;
}

// Slot for property button
void MainWindow::propertyClicked() const
{
    // show and update the properties gui
    prop->show();
    prop->update(this->bst);
    return;
}

// Slot for delete button
void MainWindow::deleteClicked() const {
    QString value = deleteValueLineEdit->text();

    if(!this->bst->deleteItem(value.toInt()))
        this->statusLabel->setText("Value is not in tree...");
    else
        this->statusLabel->setText("Value deleted.");

    this->renderArea->repaint(); // repaint to show changes to tree
    this->deleteValueLineEdit->setText(""); // clear text box
    return;
}

// Slot for insert button
void MainWindow::insertClicked() const
{
    // Get entire line of text and iterate through the list of
    // values separated by whitespace - inserting all the values
    QString values = insertValueLineEdit->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);

    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt())) // inserts 0 if text isn't an int
            this->statusLabel->setText("Duplicate valaue...");
        else
            this->statusLabel->setText("Value inserted...");
    }
    this->renderArea->repaint(); // repaint to show changes to tree
    insertValueLineEdit->setText(""); // clear text box
    return;
}

// Slot for zoom in button
void MainWindow::zoomInClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomIn();
    return;
}

// Slot for zoom out button
void MainWindow::zoomOutClicked() const {
    this->statusLabel->setText("");
    renderArea->zoomOut();
    return;
}

// Slot for load in the file menu
void MainWindow::loadFileMenu()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer",
                                 tr("Text files (*.txt)"));

    QString text;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->statusLabel->setText("Could not open file!");
        return;
    }

    this->bst->resetTree();

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        if(text != " " && text != "")
            this->bst->insert(text.toInt());
    }
    file.close();
    this->statusLabel->setText("File successfully opened!");
    return;
}

// Slot for save action in menu
void MainWindow::saveMenu()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer",
                                 tr("Text files (*.txt);;Images (*.png *.jpg)"));

    if (QFileInfo(fileName).suffix() == "txt")
    {
        std::cout<< "before getting traversal" << std::endl;
        QString text = bst->getPreOrderTraversal();
        std::cout<< "after getting traversal" << std::endl;
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            this->statusLabel->setText("File was not saved!");
            return;
        }
        QTextStream writer(&file);
        writer << text;
        writer.flush();
        file.close();
        this->statusLabel->setText("File successfully saved!");
        return;
    }

    // if not txt, save as image
    if(!this->renderArea->grab().save(fileName))
    {
        this->statusLabel->setText("Image was not saved...");
        return;
    }
    this->statusLabel->setText("Image saved...");

    return;
}

// Slot for exit action in menu
void MainWindow::exitMenu()
{
    this->close();
    return;
}

// Slot for reset action in menu
void MainWindow::resetMenu() const
{
    this->statusLabel->setText("Reset tree...");
    this->bst->resetTree();
    this->renderArea->repaint();
    return;
}

// Slot for about action in menu
void MainWindow::aboutMenu() const
{
    about->show();
    return;
}

BinarySearchTree<int>* MainWindow::getBST()
{

    BinarySearchTree<int> *bst = new BinarySearchTree<int>;

    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/BSTVisualizer/last_bst.txt";

    QString text;
    QFile file(fileName);

    // If the file doesn't exist or if it can't open, return an empty bst
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return bst;
    }

    QTextStream reader(&file);

    while (!reader.atEnd())
    {
        reader >> text;
        if (text != " " && text != "")
            bst->insert(text.toInt());
    }

    file.close();
    return bst;
}

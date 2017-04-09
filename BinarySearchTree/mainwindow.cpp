#include "mainwindow.h"
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    this->setMinimumSize(600, 400);
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    renderArea = new RenderArea;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(renderArea);
    centralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Binary Search Tree"));

    menuBar = new QMenuBar();

    prop = new BST_Properties_Window();
    prop->create();

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

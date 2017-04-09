#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    this->setMinimumSize(600, 400);
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    renderArea = new RenderArea;
    tabWidget = new QTabWidget;

    tabWidget->addTab(renderArea, tr("Tree"));
    tabWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabWidget);
    centralWidget->setLayout(mainLayout);

    setWindowTitle(tr("Binary Search Tree"));
}

MainWindow::~MainWindow()
{
    delete centralWidget;
    delete renderArea;
    delete tabWidget;
}


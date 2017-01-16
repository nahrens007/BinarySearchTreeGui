#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), bst(),
    scale(1.0)
{

    int height = 5;

    switch(height){
    case 1:{
        int arr1[3] = {50, 30, 60};

        for(int i = 0; i < 3; i++)
            bst.insert(arr1[i]);
    }
        break;
    case 2:{
        int arr2[7] = {50, 30, 60, 25, 35, 55, 65};

        for(int i = 0; i < 7; i++)
            bst.insert(arr2[i]);
    }
        break;
    case 3:{
        int arr3[15] = {50, 30, 60, 25, 35, 55, 65, 20, 27, 33, 37, 53, 57, 63, 67};

        for(int i = 0; i < 15; i++)
            bst.insert(arr3[i]);
    }
        break;
    case 4: {
        int arr4[31] = {50, 30, 20, 15, 5, 17, 25, 23, 27, 40, 35, 33, 37, 45, 43, 47, 70, 60, 55, 53, 57, 65, 63, 67, 80, 75, 85, 73, 77, 83, 87};

        for(int i = 0; i < 31; i++)
            bst.insert(arr4[i]);
    }
        break;
    case 5:{
        int arr5[65] = {50, 30, 20, 15, 5, 17, 25, 23, 27, 40, 35, 33, 37, 45, 43, 47, 70, 60, 55, 53, 57, 65, 63, 67, 80, 75, 85, 73, 77, 83, 87, 1,
                      7, 16, 18, 22, 24, 26, 28, 32, 34, 36, 38, 42, 44, 46, 48, 52, 54, 56, 58, 62, 64, 66, 68, 72, 74, 76, 78, 82, 84, 82, 84, 86, 88};

        for(int i = 0; i < 65; i++)
            bst.insert(arr5[i]);
    }
        break;
    }
    this->scale = 0.7;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QString txt = "Height: " + QString::number(bst.getTreeHeight());
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;

    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(QFont("Times", 12, QFont::Normal));
    painter.drawText(QPoint(0, 30), txt);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    bst.draw(&painter, ui->centralWidget->width(), scale);
}


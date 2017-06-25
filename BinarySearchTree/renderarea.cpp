#include "renderarea.h"
#include <QApplication>
#include <QPainter>
#include <qglobal.h>
#include <QTime>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), bst(),
    scale(1.0)
{
    int height = 5;

    switch(height){
    case -1:{
        int custArray[9] = {10, 5, 3, 7, 15, 12, 11, 13, 16};

        for(int i = 0; i < 9; i++)
            bst.insert(custArray[i]);
    }
        break;
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
    default:
        qsrand(QTime::currentTime().msec());
        for (int count = 0; count < 15; count++)
            bst.insert(qrand() % ((99 + 1) - 1) + 1);
    }
    this->scale = 1;

    this->autoSize();
}

QSize RenderArea::sizeHint() const
{
    return QSize(50, 50);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(50, 50);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    bst.draw(&painter, this->scale);
}

void RenderArea::zoomIn() {
    if(this->scale < 2.0){
        this->scale += 0.1;
        this->autoSize();
        this->repaint();
    }
}

void RenderArea::zoomOut() {
    if(this->scale > 0.2) {
        this->scale -= 0.1;
        this->autoSize();
        this->repaint();
    }
}

void RenderArea::autoSize() {
    //int height = bst.getTreeHeight();
    /* width from edge to edge of nodes = 4px(always)
     * Maximum number of leaf nodes = 2^height
     * x = 4 * 2^height + nodeDiameter * 2^height
     *
     * Pixels from top to center of root node = 30 * scale
     * yseperation (pixels between each node center to center) = nodeRadius * 5 * scale.
     * nodeRadius = 20; 100 * scale is the equivelant of yseperation.
     * y = (30 * scale) + (100 * scale) * height
     */
    //QSize size((4 * std::pow(2, height) + (40 * scale * std::pow(2, height))), ((30 * scale) + (100 * scale)) * height);
    QSize size(2000, 2000);
    this->setMinimumSize(size);
    this->resize(size);
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    // get mouse location
    switch(event->button()){
    case Qt::LeftButton:
        std::cout << "Left button release at (" << event->pos().rx() << "," << event->pos().ry() << ")" <<std::endl;
        this->zoomIn();
        break;
    case Qt::RightButton:
        std::cout << "Right button release at (" << event->pos().rx() << "," << event->pos().ry() << ")" <<std::endl;
        this->zoomOut();
        break;
    default:
        std::cout << "Something else at (" << event->pos().rx() << "," << event->pos().ry() << ")"<<std::endl;
        break;
    }
}

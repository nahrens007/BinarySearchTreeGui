#include "renderarea.h"
#include <QApplication>
#include <QPainter>
#include <qglobal.h>
#include <QTime>

RenderArea::RenderArea(BinarySearchTree<int> *bst, QWidget *parent) : QWidget(parent), bst(),
    scale(1.0)
{
    this->bst = bst;
    this->scale = 1;
    this->setStyleSheet("background-color: white;");
}


QSize RenderArea::sizeHint() const
{
    return QSize(50, 50);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(50, 50);
}

// What to do when the render area gets repaint() called
void RenderArea::paintEvent(QPaintEvent * /* event */)
{

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    bst->draw(&painter, this->scale);

    this->autoSize();
}

// Increment the scale variable and redraw
void RenderArea::zoomIn() {
    if(this->scale < 2.0){
        this->scale += 0.1;
        this->autoSize();
        this->repaint();
    }
}

// Decrement the scale variable and redraw
void RenderArea::zoomOut() {
    if(this->scale > 0.2) {
        this->scale -= 0.1;
        this->autoSize();
        this->repaint();
    }
}

// Auto size the render area based on the required size by the tree
void RenderArea::autoSize() {
    QSize size(bst->getTotalX(), bst->getTotalY());
    this->setMinimumSize(size);
    this->resize(size);
}

// Detect mouse release on render area
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

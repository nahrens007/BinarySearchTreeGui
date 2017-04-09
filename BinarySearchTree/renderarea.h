#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include "binarysearchtree.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    BinarySearchTree<int> bst;
    double scale;
    QPen pen;
    QBrush brush;
};

#endif // RENDERAREA_H

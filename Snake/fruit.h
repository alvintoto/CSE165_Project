#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsItem>

class Fruit : public QGraphicsItem
{
public:
    Fruit(qreal, qreal);

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif

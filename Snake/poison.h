#ifndef POISON_H
#define POISON_H

#include <QGraphicsItem>

class Poison : public QGraphicsItem
{
public:
    Poison(qreal, qreal);

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif

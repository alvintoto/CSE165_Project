#include <QGraphicsView>

#include "fruit.h"

constexpr int fruit_size = 10;

Fruit::Fruit(qreal x, qreal y)
{
    setPos(x, y);
}

QPainterPath Fruit::shape() const
{
    QPainterPath painterPath;
    painterPath.addEllipse(QPointF(fruit_size / 2, fruit_size / 2), fruit_size, fruit_size);
    return painterPath;
}

QRectF Fruit::boundingRect() const
{
    return QRectF{ -fruit_size / 2, -fruit_size / 2, fruit_size * 2, fruit_size * 2 };
}

void Fruit::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QColor{ 250, 0, 0 });
    painter->restore();
}



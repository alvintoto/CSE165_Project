#include <QGraphicsView>

#include "fruit.h"

static int zero = 0;
static double two = 2;
constexpr int fruit_size = 10;

Fruit::Fruit(qreal x, qreal y)
{
    setPos(x, y);
}

QPainterPath Fruit::shape() const
{
    QPainterPath painterPath;
    painterPath.addEllipse(QPointF(fruit_size / two, fruit_size / two), fruit_size, fruit_size);
    return painterPath;
}

QRectF Fruit::boundingRect() const
{
    return QRectF{ -fruit_size / two, -fruit_size / two, fruit_size * two, fruit_size * two };
}

void Fruit::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QColor{ 255, zero, zero });
    painter->restore();
}



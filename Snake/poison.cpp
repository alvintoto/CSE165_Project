#include <QGraphicsView>

#include "poison.h"

constexpr int poison_size = 10;

Poison::Poison(qreal x, qreal y)
{
    setPos(x, y);
}

QPainterPath Poison::shape() const
{
    QPainterPath painterPath;
    painterPath.addEllipse(QPointF(poison_size / 2, poison_size / 2), poison_size, poison_size);
    return painterPath;
}

QRectF Poison::boundingRect() const
{
    return QRectF{ -poison_size / 2, -poison_size / 2, poison_size * 2, poison_size * 2 };
}

void Poison::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QColor{ 0, 250, 0 });
    painter->restore();
}

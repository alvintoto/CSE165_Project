#include <QGraphicsView>

#include "poison.h"

static int zero = 0;
static double two = 2;
constexpr int poison_size = 10;

Poison::Poison(qreal x, qreal y)
{
    setPos(x, y);
}

QPainterPath Poison::shape() const
{
    QPainterPath painterPath;
    painterPath.addEllipse(QPointF(poison_size / two, poison_size / two), poison_size, poison_size);
    return painterPath;
}

QRectF Poison::boundingRect() const
{
    return QRectF{ -poison_size / two, -poison_size / two, poison_size * two, poison_size * two };
}

void Poison::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QColor{ zero, 150, zero });
    painter->restore();
}

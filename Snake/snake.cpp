#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "controller.h"
#include "snake.h"
#include "fruit.h"
#include "poison.h"

static int base_speed = 10;
constexpr int snakeSize = 10;

Snake::Snake(QGraphicsScene* scene, int length)
    : head{ Resolution::field_width / 2, Resolution::field_height / 2 }, scene{ scene },
      speed { base_speed }, xdir{ base_speed }, ydir{ 0 },
      growing { length }, direction { Directions::Right }, poisoned { false }
{

}

QPainterPath Snake::shape() const
{
    QPainterPath painterPath;
    painterPath.setFillRule(Qt::WindingFill);
    painterPath.addEllipse(QPointF{0, 0}, snakeSize, snakeSize);

    for(auto point : body)
    {
        QPointF node = mapFromScene(point);
        painterPath.addEllipse(QPointF(node.x(), node.y()), snakeSize * 0.9, snakeSize * 0.9);
    }

    return painterPath;
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    for(auto point : body) {
        maxX = point.x() > maxX ? point.x() : maxX;
        maxY = point.y() > maxY ? point.y() : maxY;
        minX = point.x() < minX ? point.x() : minX;
        minY = point.y() < minY ? point.y() : minY;
    }

    QPointF topLeft = mapFromScene(QPointF(minX, minY));
    QPointF bottomRight = mapFromScene(QPointF(maxX, maxY));

    return QRectF(QPointF(topLeft.x() - snakeSize, topLeft.y() - snakeSize),
                  QPointF(bottomRight.x() - topLeft.x() + snakeSize, bottomRight.y() - topLeft.y() + snakeSize));
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), QColor(0, 250, 250));
    painter->restore();
}

void Snake::eat(QGraphicsItem* item)
{
    growing++;
    scene->removeItem(item);
    Controller::num_fruit--;
    Controller::score++;
    if(body.count() % 2 == 0 && speed <= 25)
    {
        speed++;
    }
}

bool Snake::hit_self() const
{
    if (body.contains(head)) {
        return true;
    }

    return false;
}

bool Snake::hit_wall() const
{
    if(head.x() >= Resolution::field_width || head.x() <= 0 || head.y() >= Resolution::field_height || head.y() <= 0)
    {
        return true;
    }

    return false;
}

bool Snake::hit_poison() const {
    if (poisoned) {
        return true;
    }

    return false;
}


void Snake::collision()
{
    QList<QGraphicsItem*> collision = collidingItems();

    for(auto item : collision)
    {
        if (Fruit* fruit = dynamic_cast<Fruit*>(item))
        {
            eat(item);
        }
        else if (Poison* poison = dynamic_cast<Poison*>(item)) {
            poisoned = true;
        }
    }
}

void Snake::move()
{
    update_head();
    update_body();
    setPos(head);
}

void Snake::move_W()
{
    xdir = 0;
    ydir = -speed;
    direction = Directions::Up;
    update_head();
}

void Snake::move_A()
{
    xdir = -speed;
    ydir = 0;
    direction = Directions::Left;
    update_head();
}

void Snake::move_S()
{
    xdir = 0;
    ydir = speed;
    direction = Directions::Down;
    update_head();
}

void Snake::move_D()
{
    xdir = speed;
    ydir = 0;
    direction = Directions::Right;
    update_head();
}

void Snake::update_head()
{
    head.setX(head.x() + xdir);
    head.setY(head.y() + ydir);
}

void Snake::update_body()
{
    if(growing > 0)
    {
        growing--;
    }
    else
    {
        if(!body.isEmpty())
        {
            body.removeFirst();
        }
    }

    body.push_back(QPointF{ x(), y() });
}

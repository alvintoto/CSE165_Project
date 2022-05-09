#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "controller.h"
#include "snake.h"
#include "fruit.h"
#include "poison.h"

static double zero = 0;
static int base_speed = 10;
constexpr int snakeSize = 10;

int plus(int num1, int num2) {
    return num1 + num2;
}

int minus(int num1, int num2) {
    return num1 - num2;
}

Snake::Snake(QGraphicsScene* scene, int length)
{
    this->head = QPointF(Resolution::field_width / 2, Resolution::field_height / 2);
    this->scene = scene;
    this->speed = base_speed;
    this->xdir = base_speed;
    this->ydir = zero;
    this->growing = length;
    this->direction = Directions::Right;
    this->poisoned = false;
}

QPainterPath Snake::shape() const
{
    QPainterPath painterPath;
    painterPath.setFillRule(Qt::WindingFill);
    painterPath.addEllipse(QPointF{zero, zero}, snakeSize, snakeSize);

    for(auto point : body)
    {
        QPointF node = mapFromScene(point);
        painterPath.addEllipse(QPointF(node.x(), node.y()), snakeSize * 0.7, snakeSize * 0.7);
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
    painter->fillPath(shape(), QColor(zero, 255, 255));
    painter->restore();
}

void Snake::eat(QGraphicsItem* item)
{
    growing = plus(growing, 1);
    scene->removeItem(item);
    Controller::num_fruit = minus(Controller::num_fruit, 1);
    Controller::score = plus(Controller::score, 1);
    if(body.count() % 2 == zero && speed <= 25)
    {
        speed = plus(speed, 1);
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
    if(head.x() >= Resolution::field_width || head.x() <= zero || head.y() >= Resolution::field_height || head.y() <= zero)
    {
        return true;
    }

    return false;
}

bool Snake::hit_poison() const
{
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
        if (Poison* poison = dynamic_cast<Poison*>(item)) {
            poisoned = true;
        }
        else if (Fruit* fruit = dynamic_cast<Fruit*>(item))
        {
            eat(item);
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
    direction = Directions::Up;
    xdir = zero;
    ydir = -speed;
    update_head();
}

void Snake::move_A()
{
    direction = Directions::Left;
    xdir = -speed;
    ydir = zero;
    update_head();
}

void Snake::move_S()
{
    direction = Directions::Down;
    xdir = zero;
    ydir = speed;
    update_head();
}

void Snake::move_D()
{
    direction = Directions::Right;
    xdir = speed;
    ydir = zero;  
    update_head();
}

void Snake::update_head()
{
    head.setX(plus(head.x(), xdir));
    head.setY(plus(head.y(), ydir));
}

void Snake::update_body()
{
    if(growing > zero)
    {
        growing = minus(growing, 1);
    }
    else
    {
        if(body.isEmpty() == false)
        {
            body.removeFirst();
        }
    }

    body.append(QPointF{ x(), y() });
}

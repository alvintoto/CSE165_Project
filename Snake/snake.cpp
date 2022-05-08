#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "controller.h"
#include "snake.h"
#include "fruit.h"
#include "poison.h"

static int zero = 0;
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
    head = QPointF(Resolution::field_width / 2, Resolution::field_height / 2);
    this->scene = scene;
    speed = base_speed;
    xdir = base_speed;
    ydir = zero;
    growing = length;
    direction = Directions::Right;
    poisoned = false;
}

QPainterPath Snake::shape() const
{
    QPainterPath painterPath;
    painterPath.setFillRule(Qt::WindingFill);
    painterPath.addEllipse(QPointF{zero, zero}, snakeSize, snakeSize);

    for(auto point : body)
    {
        QPointF node = mapFromScene(point);
        painterPath.addEllipse(QPointF(node.x(), node.y()), snakeSize * 0.75, snakeSize * 0.75);
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
    xdir = zero;
    ydir = -speed;
    direction = Directions::Up;
    update_head();
}

void Snake::move_A()
{
    xdir = -speed;
    ydir = zero;
    direction = Directions::Left;
    update_head();
}

void Snake::move_S()
{
    xdir = zero;
    ydir = speed;
    direction = Directions::Down;
    update_head();
}

void Snake::move_D()
{
    xdir = speed;
    ydir = zero;
    direction = Directions::Right;
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
        if(!body.isEmpty())
        {
            body.removeFirst();
        }
    }

    body.append(QPointF{ x(), y() });
}

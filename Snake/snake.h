#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPainter>

#include "constants.h"

class Snake : public QGraphicsItem
{
public:
    Snake(QGraphicsScene*, int);
    ~Snake() {}

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);


    bool hit_self() const;
    bool hit_wall() const;
    bool hit_poison() const;
    void collision();

    long int xdir;
    long int ydir;

    bool poisoned;

    void move();
    void move_W();
    void move_A();
    void move_S();
    void move_D();

    Directions get_direction() const { return direction; }

private:
    QPointF head;
    QList<QPointF> body;

    QGraphicsScene* scene = nullptr;

    long int speed;

    Directions direction;

    long int length;
    long int growing;

    void eat(QGraphicsItem*);

    void update_head();
    void update_body();
};

#endif

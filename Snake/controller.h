#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QElapsedTimer>

#include "snake.h"
#include "fruit.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QGraphicsScene*, QObject* parent, int, int);
    ~Controller() override;

    static int num_fruit;
    static int score;

    bool is_paused;

public slots:
    void create_fruit();
    void create_poison();
    void move_snake();

private:
    QGraphicsScene* scene = nullptr;
    Snake* snake = nullptr;

    QElapsedTimer* game_timer = nullptr;
    QTimer* snake_timer = nullptr;
    QTimer* fruit_timer = nullptr;
    QTimer* poison_timer = nullptr;

    int time;
    int length;

    void start_timers() const;
    void stop_timers() const;

    void collision();
    void check_hit() const;

    bool hit_wall() const;
    bool hit_self() const;
    bool hit_poison() const;

    bool fruit_count() const;
    bool poison_count() const;

    void dead();
    void restart();
    void quit() const;

    void pause();
    void resume();

    QString game_over() const;

    void keyPressEvent(QKeyEvent*);
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif

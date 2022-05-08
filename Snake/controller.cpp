#include <QEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QApplication>

#include "controller.h"
#include "constants.h"
#include "fruit.h"
#include "poison.h"

static int zero = 0;

int add(int num1, int num2) {
    return num1 + num2;
}

long int Controller::num_fruit = zero;
long int Controller::score = zero;

Controller::Controller(QGraphicsScene* scene, QObject* parent, int time, int length) : QObject{ parent }
{
    this->scene = scene;
    this->snake = new Snake(scene, length);
    this->time = time * 60000;
    this->length = length;
    is_paused = false;

    scene->addItem(snake);
    scene->installEventFilter(this);

    fruit_timer = new QTimer();
    connect(fruit_timer, SIGNAL(timeout()), this, SLOT(create_fruit()));

    poison_timer = new QTimer();
    connect(poison_timer, SIGNAL(timeout()), this, SLOT(create_poison()));

    snake_timer = new QTimer();
    connect(snake_timer, SIGNAL(timeout()), this, SLOT(move_snake()));

    game_timer = new QElapsedTimer();

    start_timers();
}

Controller::~Controller()
{
    delete snake;
    delete fruit_timer;
    delete poison_timer;
    delete snake_timer;
    delete game_timer;
}

void Controller::move_snake()
{
    if(game_timer->elapsed() >= time)
    {
        dead();
    }
    collision();
    snake->move();
    snake->setFocus();
}

void Controller::start_timers() const
{
    game_timer->start();
    fruit_timer->start(300);
    poison_timer->start(3500);
    snake_timer->start(35);
}

void Controller::stop_timers() const
{
    fruit_timer->stop();
    poison_timer->stop();
    snake_timer->stop();
}

void Controller::create_fruit()
{
    if (fruit_count())
    {
        return;
    }

    scene->addItem(new Fruit(rand() % (Resolution::field_width - 10) + 5, rand() % (Resolution::field_height - 10) + 5));
    num_fruit = add(num_fruit, 1);
}

void Controller::create_poison()
{
    scene->addItem(new Poison(rand() % (Resolution::field_width - 10) + 5, rand() % (Resolution::field_height - 10) + 5));
}

void Controller::collision()
{
    if(hit_wall() || hit_self() || hit_poison())
    {
        dead();
    }

    check_hit();
}

bool Controller::hit_wall() const
{
    if (snake->hit_wall()) {
        return true;
    }

    return false;
}

bool Controller::hit_self() const
{
    if (snake->hit_self()) {
        return true;
    }

    return false;
}

bool Controller::hit_poison() const
{
    if (snake->hit_poison()) {
        return true;
    }

    return false;
}

void Controller::check_hit() const
{
    snake->collision();
}

bool Controller::fruit_count() const
{
    if (num_fruit >= 4) {
        return true;
    }

    return false;
}

void Controller::dead()
{
    stop_timers();

    QMessageBox::StandardButton reply{ QMessageBox::question(nullptr, "GAME OVER", game_over(), QMessageBox::Yes | QMessageBox::No) };

    switch(reply) {
    case QMessageBox::Yes:
        restart();
        break;
    case QMessageBox::No:
        quit();
        break;
    default:
        break;
    }
}

void Controller::restart()
{
    num_fruit = zero;
    score = zero;
    scene->clear();
    snake = new Snake(scene, length);
    scene->addItem(snake);
    start_timers();
}

void Controller::quit() const
{
    QApplication::quit();
}

QString Controller::game_over() const
{
    QString message;
    message.append("Score: ");
    message.append(QString::number(score));
    message.append("\nDo you want to play again?");
    return message;
}

bool Controller::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        keyPressEvent(dynamic_cast<QKeyEvent*>(event));
        return true;
    }
    else
    {
        return QObject::eventFilter(watched, event);
    }
}


void Controller::keyPressEvent(QKeyEvent* keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_W:
    {
        if(snake->get_ydir() <= zero && snake->get_direction() != Directions::Up)
        {
            snake->move_W();
        }
        break;
    }
    case Qt::Key_A:
    {
        if(snake->get_xdir() <= zero && snake->get_direction() != Directions::Left)
        {
            snake->move_A();
        }
        break;
    }
    case Qt::Key_S:
    {
        if(snake->get_ydir() >= zero && snake->get_direction() != Directions::Down)
        {
            snake->move_S();
        }
        break;
    }
    case Qt::Key_D:
    {
        if(snake->get_xdir() >= zero && snake->get_direction() != Directions::Right)
        {
            snake->move_D();
        }
        break;
    }
    }
}


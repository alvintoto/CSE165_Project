#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsView>
#include <QWidget>
#include <QMainWindow>

#include "controller.h"

class Field : public QGraphicsView
{
    Q_OBJECT
public:
    Field();
    ~Field();

private:
    QGraphicsScene* scene = nullptr;
    Controller* controller = nullptr;
};

#endif

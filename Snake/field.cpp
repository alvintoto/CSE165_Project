#include "field.h"

static int zero = 0;

Field::Field()
{
    scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);
    setFixedSize(Resolution::field_width, Resolution::field_height);
    setSceneRect(zero, zero, Resolution::field_width, Resolution::field_height);

    controller = new Controller{scene, nullptr, 6, 6};

    show();
}

Field::~Field()
{
    delete controller;
    delete scene;
}



















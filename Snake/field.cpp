#include "field.h"

Field::Field(int time, int length)
{
    scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);
    setFixedSize(Resolution::field_width, Resolution::field_height);
    setSceneRect(0, 0, Resolution::field_width, Resolution::field_height);

    controller = new Controller{scene, nullptr, time, length};

    show();
}

Field::~Field()
{
    delete controller;
    delete scene;
}



















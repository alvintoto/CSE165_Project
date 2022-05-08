#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "field.h"
#include "mainwindow.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();

public slots:
    void start_game();
    void quit_game();

private:
    Field* field = nullptr;
    MainWindow* main_window = nullptr;
};

#endif

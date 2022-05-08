#include <QApplication>
#include <random>

#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    Game* window = new Game();

    return app.exec();
}

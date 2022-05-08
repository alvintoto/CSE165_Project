#include <QApplication>
#include <random>

#include "game.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);

    Game* window = new Game();

    return a.exec();
}

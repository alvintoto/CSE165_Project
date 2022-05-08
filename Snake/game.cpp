#include "game.h"

Game::Game()
    : main_window { new MainWindow() }
{
    connect(main_window, &MainWindow::start_game, this, &Game::start_game);
    connect(main_window, &MainWindow::quit_game, this, &Game::quit_game);
    main_window->show();
}

Game::~Game()
{
    delete field;
    delete main_window;
}

void Game::start_game()
{
    main_window->close();
    field = new Field(main_window->get_time(), main_window->get_length());
}

void Game::quit_game()
{
    QApplication::quit();
}

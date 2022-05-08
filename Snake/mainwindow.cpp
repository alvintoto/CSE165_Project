#include "mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_start_game_clicked()
{
    emit start_game();
}

void MainWindow::on_quit_game_clicked()
{
    emit quit_game();
}

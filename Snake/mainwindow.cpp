#include "mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
{
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

int MainWindow::get_time() const
{
    return time;
}

int MainWindow::get_length() const
{
    return length;
}

void MainWindow::on_start_game_clicked()
{
    length = 6;
    time = 6;
    emit start_game();
}

void MainWindow::on_quit_game_clicked()
{
    emit quit_game();
}

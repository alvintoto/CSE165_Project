#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "ui_mainwindow.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow ui;

private slots:
    void on_start_game_clicked();
    void on_quit_game_clicked();

signals:
    void start_game();
    void quit_game();
};

#endif

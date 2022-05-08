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

    void set_length(int value) { length = value; }
    int get_length() const;

    void set_time(int value) { time = value; }
    int get_time() const;

private:
    Ui::MainWindow ui;

    int time;
    int length;

private slots:
    void on_start_game_clicked();
    void on_quit_game_clicked();

signals:
    void start_game();
    void quit_game();
};

#endif

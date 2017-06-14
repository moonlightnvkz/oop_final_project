#pragma once

#include <QMainWindow>

class Controller;
class GameBoardView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GameBoardView *get_view();

    void add_controller(Controller *controller);

signals:
    void settings_changed();

public slots:
    void show_settings();

    void on_restart();

private:
    Ui::MainWindow *ui;

    Controller *controller;
};
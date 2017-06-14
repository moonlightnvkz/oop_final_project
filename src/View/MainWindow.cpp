#include <QtWidgets/QMessageBox>
#include <fstream>
#include "include/View/TableauStackView.h"
#include "include/View/SettingsDialog.h"
#include "include/SettingsWriter.h"
#include "include/View/MainWindow.h"
#include "include/View/GameBoardView.h"
#include "include/Controller/Controller.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(nullptr)
{
    ui->setupUi(this);
    setFixedSize(720, 480);
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(show_settings()));
    connect(this, SIGNAL(settings_changed()), ui->graphicsView, SLOT(apply_settings()));
    connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(on_restart()));
}

MainWindow::~MainWindow()
{
    delete ui;
    std::ofstream os("settings");
    SettingsWriter::write(os);
}

void MainWindow::show_settings() {
    SettingsDialog *dialog = new SettingsDialog(this);
    int res = dialog->exec();
    if (res == QDialog::Accepted) {
        if (dialog->game_rules_changed()) {
            QMessageBox msg_box;
            msg_box.setText("The rules of the game have changed.");
            msg_box.setInformativeText("Restart the game to apply new settings.");
            msg_box.setStandardButtons(QMessageBox::Ok);
            msg_box.setDefaultButton(QMessageBox::Ok);
            // Because for some reason setFixedSize() doesn't work...
            msg_box.setStyleSheet("QLabel{min-width:300 px; qproperty-alignment: AlignCenter; font-size: 16px;} "
                                          "QPushButton{font-size: 14px;}");
            msg_box.exec();
        }
        emit settings_changed();

    }
}

void MainWindow::add_controller(Controller *controller) {
    this->controller = controller;
    ui->graphicsView->add_controller(controller);
}

GameBoardView *MainWindow::get_view() {
    return ui->graphicsView;
}

void MainWindow::on_restart() {
    controller->restart_game();
}

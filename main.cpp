#include <QtWidgets/QApplication>
#include <fstream>
#include "include/View/CardTextureAtlas.h"
#include "include/Model/GameBoard.h"
#include "include/SettingsReader.h"
#include "include/Settings.h"
#include "include/View/MainWindow.h"
#include "include/Controller/Controller.h"
#include "include/View/GameBoardView.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::ifstream is("settings");
    if (!SettingsReader::read(is)) {
        Settings::GetInstance().load_default();
    }
    CardTextureAtlas::GetInstance().load_textures();
    MainWindow w;
    GameBoard gameBoard;
    Controller controller(&gameBoard, w.get_view());
    w.add_controller(&controller);
    w.show();
    return a.exec();
}
cmake_minimum_required(VERSION 3.7)
project(SolitaireKlondike)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        include/Model/Card.h
        src/Model/CardDeck.cpp include/Model/CardDeck.h
        include/Model/FoundationStack.h src/Model/Foundation.cpp
        include/Model/Foundation.h
        include/Model/Tableau.h
        src/Model/Waste.cpp include/Model/Waste.h
        include/Model/CardContainer.h
        src/Model/FoundationStack.cpp
        src/Model/TableauStack.cpp include/Model/TableauStack.h
        src/Model/CardContainer.cpp src/Model/Tableau.cpp
        src/Controller/Controller.cpp include/Controller/Controller.h
        src/Model/GameBoard.cpp include/Model/GameBoard.h src/Settings.cpp include/Settings.h src/SettingsReader.cpp include/SettingsReader.h)

set (GUI_SOURCES
        src/View/MainWindow.cpp include/View/MainWindow.h
        src/View/TextureManager.cpp include/View/TextureManager.h
        src/View/GameBoardView.cpp include/View/GameBoardView.h
        src/View/CardView.cpp include/View/CardView.h
        src/View/CardContainerView.cpp include/View/CardContainerView.h
        src/View/TableauStackView.cpp include/View/TableauStackView.h
        src/View/StackLayoutView.cpp include/View/StackLayoutView.h
        src/View/CardTextureAtlas.cpp include/View/CardTextureAtlas.h src/View/SettingsDialog.cpp include/View/SettingsDialog.h src/SettingsWriter.cpp include/SettingsWriter.h)

add_executable(SolitaireKlondike_exe main.cpp)
add_library(SolitaireKlondike_lib SHARED ${SOURCE_FILES} ${GUI_SOURCES})
target_link_libraries(SolitaireKlondike_lib Qt5::Core Qt5::Widgets Qt5::Gui)
target_link_libraries(SolitaireKlondike_exe SolitaireKlondike_lib)

set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.7/gcc_64)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
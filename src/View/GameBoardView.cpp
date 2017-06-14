//
// Created by moonlightnvkz on 29.05.17.
//

#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QtWidgets/QMessageBox>
#include <QApplication>
#include <QtWidgets/QGridLayout>
#include "include/View/TextureManager.h"
#include "include/Settings.h"
#include "include/Controller/Controller.h"
#include "include/View/CardView.h"
#include "include/View/GameBoardView.h"
#include "include/View/StackLayoutView.h"
#include "include/View/TableauStackView.h"
#include "include/View/CardContainerView.h"

GameBoardView::GameBoardView(QWidget *parent)
        : QGraphicsView(parent) {
    Settings &settings = Settings::GetInstance();
    background = TextureManager::GetInstance().load("res/background.png");
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setScene(new QGraphicsScene(rect(), this));
    deck = new CardContainerView();
    deck->setPos(10, 10);
    waste = new CardContainerView();
    waste->setPos(100, 10);
    foundation = new StackLayoutView<CardContainerView>();
    foundation->setPos(250, 10);
    tableau = new StackLayoutView<TableauStackView>();
    tableau->setPos(10, 200);

    connect(deck, SIGNAL(mouse_pressed()), this, SLOT(deck_pressed()));
    connect(waste, SIGNAL(drag_happen(size_t)), this, SLOT(card_taken_from_waste(size_t)));
    connect(foundation, SIGNAL(tale_taken(unsigned, size_t)), this, SLOT(card_from_foundation_is_taken(unsigned, size_t)));
    connect(tableau, SIGNAL(tale_taken(unsigned, size_t)), this, SLOT(tableau_stack_tale_is_taken(unsigned, size_t)));
    connect(foundation, SIGNAL(card_dropped(unsigned)), this, SLOT(card_dropped_to_foundation(unsigned)));
    connect(tableau, SIGNAL(card_dropped(unsigned)), this, SLOT(card_dropped_to_tableau(unsigned)));
    connect(waste, SIGNAL(drag_release_back()), this, SLOT(release_back()));
    connect(tableau, SIGNAL(drag_release_back()), this, SLOT(release_back()));
    connect(foundation, SIGNAL(drag_release_back()), this, SLOT(release_back()));

    scene()->addItem(deck);
    scene()->addItem(waste);
    scene()->addItem(foundation);
    scene()->addItem(tableau);

    apply_settings();
}

GameBoardView::~GameBoardView() {

}

//void GameBoardView::drawBackground(QPainter *painter, const QRectF &rect) {
//    const QPixmap &pmap = TextureManager::GetInstance().get_by_id(background);
//    painter->drawPixmap(this->rect(), pmap, pmap.rect());
//}

void GameBoardView::deck_pressed() {
    qDebug() << "GameBoardView::deck_pressed";
    controller->turn_deck();
}

void GameBoardView::card_taken_from_waste(size_t) {
    qDebug() << "GameBoardView::card_taken_from_waste";
    controller->card_from_waste_is_taken();
}

void GameBoardView::card_from_foundation_is_taken(unsigned i, size_t) {
    qDebug() << "GameBoardView::card_from_foundation_is_taken";
    controller->card_from_foundation_is_taken(i);
}

void GameBoardView::card_dropped_to_tableau(unsigned i) {
    qDebug() << "GameBoardView::card_dropped_to_tableau";
    controller->put_to_tableau_stack(i);
}

void GameBoardView::card_dropped_to_foundation(unsigned i) {
    qDebug() << "GameBoardView::card_dropped_to_foundation";
    controller->put_to_foundation_stack(i);
}

void GameBoardView::tableau_stack_tale_is_taken(unsigned i, size_t amount) {
    qDebug() << "GameBoardView::tableau_stack_tale_is_taken";
    controller->tableau_stack_tale_is_taken(i, amount);
}

void GameBoardView::release_back() {
    qDebug() << "GameBoardView::release_back";
    controller->release_back();
}

bool GameBoardView::show_congratulations_window() {
    QMessageBox msg_box;
    msg_box.setText("Congratulations!");
    msg_box.setInformativeText("Do you want to play again?");
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setDefaultButton(QMessageBox::Yes);
    // Because for some reason setFixedSize() doesn't work...
    msg_box.setStyleSheet("QLabel{min-width:300 px; qproperty-alignment: AlignCenter; font-size: 16px;} "
                                  "QPushButton{font-size: 14px;}");
    int res = msg_box.exec();
    switch (res) {
        case QMessageBox::Yes: return true;
        default: return false;
    }
}

void GameBoardView::apply_settings() {
    Settings::Appearance &appearance = Settings::GetInstance().appearance;
    foundation->adjust_h_space(appearance.foundation_spacing);
    tableau->adjust_h_space(appearance.tableau_spacing);
    for(auto & s : tableau->get_stacks()) {
        s->adjust_v_shift(appearance.tableau_shift);
    }
    setBackgroundBrush(QColor(appearance.background_color.red,
                              appearance.background_color.green,
                              appearance.background_color.blue));
    fit_in_view();
}

void GameBoardView::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);
    fit_in_view();
}

void GameBoardView::fit_in_view() {
    QRectF rect = scene()->itemsBoundingRect();
    rect.setHeight(rect.height() + 15);     // margin
    rect.setWidth(rect.width() + 15);
    fitInView(rect, Qt::KeepAspectRatio);
}

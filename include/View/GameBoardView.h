//
// Created by moonlightnvkz on 29.05.17.
//

#pragma once


#include <QtWidgets/QGraphicsView>
#include "include/View/StackLayoutView.h"

class Controller;
class CardContainerView;
class TableauStackView;
class CardView;

class GameBoardView : public QGraphicsView {
    Q_OBJECT
public:
    GameBoardView(QWidget *parent = nullptr);

    virtual ~GameBoardView() override;

    void add_controller(Controller *controller) { this->controller = controller; }

    /// \return true if new game has chosen
    bool show_congratulations_window();

    void fit_in_view();

    StackLayoutView<TableauStackView> *tableau;

    StackLayoutView<CardContainerView> *foundation;

    CardContainerView *deck;

    CardContainerView *waste;
public slots:

    void on_deck_pressed();

    void on_card_taken_from_waste(const size_t);

    /// size_t is for compatibility
    void on_card_from_foundation_is_taken(const unsigned i, const size_t);

    void on_tableau_stack_tale_is_taken(const unsigned i, const size_t idx_from_back);

    void on_card_dropped_to_tableau(const unsigned i);

    void on_card_dropped_to_foundation(const unsigned i);

    void on_release_back();

    void apply_settings();

protected:
    virtual void showEvent(QShowEvent *event) override;

//    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

    unsigned background;

    Controller *controller;
};



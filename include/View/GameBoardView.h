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

    void deck_pressed();

    void card_taken_from_waste(size_t);

    /// size_t is for compatibility
    void card_from_foundation_is_taken(unsigned i, size_t);

    void tableau_stack_tale_is_taken(unsigned i, size_t idx_from_back);

    void card_dropped_to_tableau(unsigned i);

    void card_dropped_to_foundation(unsigned i);

    void release_back();

    void apply_settings();

protected:
    virtual void showEvent(QShowEvent *event) override;

//    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

    unsigned background;

    Controller *controller;
};



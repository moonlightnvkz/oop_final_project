//
// Created by moonlightnvkz on 29.05.17.
//

#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <cassert>
#include "include/View/TextureManager.h"
#include "include/View/CardContainerView.h"
#include "include/View/CardView.h"
#include "include/Model/CardContainer.h"

unsigned CardContainerView::background;

bool CardContainerView::background_loaded = false;

CardContainerView::CardContainerView(QGraphicsItem *parent)
        : QGraphicsObject (parent) {
    if (!background_loaded) {
        background = TextureManager::GetInstance().load("res/stackBg.png");
        background_loaded = true;
    }
    setAcceptDrops(true);
}

CardContainerView::CardContainerView(const CardContainer &container, QGraphicsItem *parent)
        : QGraphicsObject(parent) {
    if (!background_loaded) {
        background = TextureManager::GetInstance().load("res/stackBg.png");
        background_loaded = true;
    }
    setAcceptDrops(true);
    update(container);
}

CardContainerView::~CardContainerView() {

}

void CardContainerView::update(const CardContainer &container) {
    for (auto c : cards) {
        disconnect(c, SIGNAL(mouse_pressed()), this, SLOT(on_card_mouse_pressed()));
        disconnect(c, SIGNAL(drag_happen()), this, SLOT(on_card_drag_happen()));
        c->deleteLater();
    }
    cards.clear();
    size_t size = container.size();
    if (size > 0) {
        for (size_t i = size - 1;; --i) {
            CardView *c = new CardView(container.peek_card(i), this);
            connect(c, SIGNAL(mouse_pressed()), this, SLOT(on_card_mouse_pressed()));
            connect(c, SIGNAL(drag_happen()), this, SLOT(on_card_drag_happen()));
            cards.push_back(c);
            if (i == 0) {
                break;
            }
        }
    }
}

void CardContainerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, TextureManager::GetInstance().get_by_id(background));
}

QRectF CardContainerView::boundingRect() const {
    return TextureManager::GetInstance().get_by_id(background).rect();
}

void CardContainerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    event->accept();
}

void CardContainerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    Q_UNUSED(event);
}

void CardContainerView::dropEvent(QGraphicsSceneDragDropEvent *event) {
    event->accept();
    emit card_dropped();
}

void CardContainerView::on_card_mouse_pressed() {
    emit mouse_pressed();
}

void CardContainerView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    emit mouse_pressed();
}

QObject *CardContainerView::drag_processing(const QPixmap &pmap, QRectF boundingRect) {
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    drag->setMimeData(mimeData);
    drag->setPixmap(pmap);
    drag->setHotSpot(boundingRect.center().toPoint());
    drag->exec();
    return drag->target();
}

void CardContainerView::on_card_drag_happen() {
    const CardView *sender = dynamic_cast<CardView *>(QObject::sender());
    if (!sender || sender->get_side() == eSide::Back) {
        return;
    }
    size_t size = cards.size();
    assert(size != 0);
    size_t amount;
    for (size_t i = size - 1; ; --i) {
        if (cards[i] == sender) {
            amount = size - i;
            emit drag_happen(amount);
            break;
        }
        assert(i != 0);
    }
    for (size_t i = size - amount; i < size; ++i) {
        cards[i]->hide();
    }
    QPixmap pmap = create_pixmap_for_drag(amount);
    if (!drag_processing(pmap, sender->boundingRect())) {
        emit drag_release_back();
    }
    for (size_t i = size - amount; i < size; ++i) {
        cards[i]->show();
    }
}

QPixmap CardContainerView::create_pixmap_for_drag(size_t amount) const {
    Q_UNUSED(amount);
    assert(cards.size() > 0);
    return cards.back()->get_pixmap();
}

//
// Created by moonlightnvkz on 26.05.17.
//
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QApplication>
#include "include/View/CardTextureAtlas.h"
#include "include/View/CardView.h"

CardView::CardView(const Card *card, QGraphicsItem *parent)
        : QGraphicsObject(parent),
          pmap(CardTextureAtlas::GetInstance().
                  get_texture(card->get_suit(), card->get_side(), card->get_rank())) {
    setCursor(Qt::OpenHandCursor);
    side = card->get_side();
}

CardView::~CardView() {

}

void CardView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0, 0, pmap);
}

QRectF CardView::boundingRect() const {
    return QRectF(0, 0, pmap.width(), pmap.height());
}

void CardView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
    emit mouse_pressed();
}

void CardView::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
                .length() < QApplication::startDragDistance()) {
        return;
    }
    emit drag_happen();
    setCursor(Qt::OpenHandCursor);
}

void CardView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setCursor(Qt::OpenHandCursor);
}

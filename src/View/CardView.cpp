//
// Created by moonlightnvkz on 26.05.17.
//
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <include/View/CardTextureAtlas.h>
#include <QtWidgets/QApplication>
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


void CardView::update(const Card *card) {

}

void CardView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0, 0, pmap);
}

QRectF CardView::boundingRect() const {
    return QRectF(0, 0, pmap.width(), pmap.height());
}

void CardView::mousePressEvent(QGraphicsSceneMouseEvent *event) {
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
    setCursor(Qt::OpenHandCursor);
}

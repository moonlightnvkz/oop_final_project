//
// Created by moonlightnvkz on 26.05.17.
//

#pragma once

#include <QGraphicsObject>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsItem>
#include "include/Model/Card.h"

class Card;

class CardView : public QGraphicsObject {
    Q_OBJECT
public:
    explicit CardView(const Card *card, QGraphicsItem *parent);

    virtual QRectF boundingRect() const override;

    virtual ~CardView() override;

    void update(const Card *card);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const QPixmap &get_pixmap() const { return pmap; }

    Card::eSide get_side() const { return side; }

signals:
    void mouse_pressed();

    void drag_happen();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    const QPixmap &pmap;

    Card::eSide side;
};
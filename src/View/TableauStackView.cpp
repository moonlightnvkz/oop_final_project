//
// Created by moonlightnvkz on 29.05.17.
//

#include <QtGui/QPainter>
#include <cassert>
#include "include/View/TextureManager.h"
#include "include/View/TableauStackView.h"
#include "include/Model/TableauStack.h"
#include "include/View/CardView.h"

TableauStackView::TableauStackView(const CardContainer &container, QGraphicsItem *parent, int v_shift)
        : CardContainerView(container, parent) {
    adjust_v_shift(v_shift);
}

TableauStackView::~TableauStackView() {

}

QRectF TableauStackView::boundingRect() const {
    const QPixmap &bg = TextureManager::GetInstance().get_by_id(background);
    if (cards.size() == 0) {
        return bg.rect();
    }
    QRectF rect = cards.back()->boundingRect();
    // maximum number of cards in a stack - 23
    return QRectF(0, 0, bg.width(), 15 * v_shift + rect.height());
}

void TableauStackView::update(const CardContainer &container) {
    CardContainerView::update(container);
    qreal shift = 0;
    for (auto &c : cards) {
        c->setY(c->y() + shift);
        shift += v_shift;
    }
}

QPixmap TableauStackView::create_pixmap_for_drag(size_t amount) const {
    assert(cards.size() > 0);
    size_t size = cards.size();
    QRect first_r = cards[size - amount]->boundingRect().toRect();
    QPoint first_p = cards[size - amount]->pos().toPoint();
    QPoint last_p = cards.back()->pos().toPoint();
    QPixmap pmap(first_r.width(), last_p.y() - first_p.y() + first_r.height());
    pmap.fill(Qt::transparent);
    QPainter painter(&pmap);
    int shift = 0;
    for (size_t i = size - amount; i < size; ++i) {
        painter.drawPixmap(0, shift, cards[i]->get_pixmap());
        shift += v_shift;
    }
    return pmap;
}

void TableauStackView::adjust_v_shift(int new_v_shift) {
    v_shift = new_v_shift;
    qreal shift = 0;
    for (auto &c : cards) {
        c->setY(shift);
        shift += v_shift;
    }
}

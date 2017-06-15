//
// Created by moonlightnvkz on 29.05.17.
//

#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <functional>
#include <cassert>
#include "include/View/TableauStackView.h"
#include "include/View/StackLayoutView.h"

template<typename T>
StackLayoutView<T>::StackLayoutView(int h_space, QGraphicsItem *parent)
        : QGraphicsItemGroup(parent), h_space(h_space) {
    QGraphicsItemGroup::setHandlesChildEvents(false);
}

template<typename T>
StackLayoutView<T>::StackLayoutView(const std::vector<std::reference_wrapper<const CardContainer>> &stacks,
                                    int h_space, QGraphicsItem *parent)
        : QGraphicsItemGroup(parent), h_space(h_space) {
    load_stacks(stacks);
    QGraphicsItemGroup::setHandlesChildEvents(false);
}

template<typename T>
StackLayoutView<T>::~StackLayoutView() {

}

template<typename T>
void StackLayoutView<T>::load_stacks(const std::vector<std::reference_wrapper<const CardContainer>> &stacks) {
    for (auto s : this->stacks) {
        disconnect(s, SIGNAL(card_dropped()), this, SLOT(on_card_dropped()));
        disconnect(s, SIGNAL(drag_happen(size_t)), this, SLOT(on_drag_happen(size_t)));
        disconnect(s, SIGNAL(drag_release_back()), this, SLOT(on_drag_release_back()));
        s->deleteLater();
    }
    this->stacks.clear();
    for (const auto s : stacks) {
        T *p = new T(s, this);
        this->stacks.push_back(p);
        connect(p, SIGNAL(card_dropped()), this, SLOT(on_card_dropped()));
        connect(p, SIGNAL(drag_happen(size_t)), this, SLOT(on_drag_happen(size_t)));
        connect(p, SIGNAL(drag_release_back()), this, SLOT(on_drag_release_back()));
    }
    adjust_h_space(h_space);
}

template<typename T>
void StackLayoutView<T>::update(const CardContainer &stack, unsigned i) {
    stacks.at(i)->update(stack);
}

template<typename T>
QRectF StackLayoutView<T>::boundingRect() const {
    if (stacks.size() == 0) {
        return QRectF();
    }
    QRectF rect = stacks[0]->boundingRect();
    T *right = stacks.back();
    return QRectF(0, 0, right->x() + rect.width(), rect.height());
}

template<typename T>
void StackLayoutView<T>::on_card_dropped() {
    QObject *sender = QObject::sender();
    emit card_dropped(get_stack_idx(sender));
}

template<typename T>
void StackLayoutView<T>::on_drag_happen(size_t amount) {
    QObject *sender = QObject::sender();
    emit tale_taken(get_stack_idx(sender), amount);
}

template<typename T>
unsigned StackLayoutView<T>::get_stack_idx(void *p) {
    size_t size = stacks.size();
    for (unsigned i = 0; i < size; ++i) {
        if (stacks[i] == p) {
            return i;
        }
    }
    // Should never happen
    assert(true);
    return 0;
}

template<typename T>
void StackLayoutView<T>::on_drag_release_back() {
    emit drag_release_back();
}

template<typename T>
void StackLayoutView<T>::adjust_h_space(int new_h_space) {
    h_space = new_h_space;
    qreal shift = 0;
    for (const auto s : stacks) {
        s->setX(shift);
        shift += s->boundingRect().width() + h_space;
    }
}

template class StackLayoutView<CardContainerView>;

template class StackLayoutView<TableauStackView>;

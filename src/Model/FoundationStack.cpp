//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "include/Model/FoundationStack.h"

FoundationStack::FoundationStack(FoundationStack &&stack)
        : CardContainer(std::move(stack.cards)), order(stack.order) {

}

FoundationStack::FoundationStack(RankOrder order)
        : order(order) {

}

bool FoundationStack::is_suitable(const Card *card) const {
    if (card == nullptr) {
        return true;
    }
    const Card *top = peek_card();
    bool ascending = order == RankOrder::Ascending;
    if (top == nullptr) {
        return card->get_rank() == (ascending ? Card::eRank::Ace : Card::eRank::King);
    }
    int inc = ascending ? 1 : -1;
    return static_cast<int>(top->get_rank()) == static_cast<int>(card->get_rank()) - inc
           && top->get_suit() == card->get_suit();
}

FoundationStack &FoundationStack::operator=(FoundationStack &&that) {
    if (this != &that) {
        this->cards = std::move(that.cards);
        order = that.order;
    }
    return *this;
}

//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "include/Model/TableauStack.h"

TableauStack::TableauStack(std::vector<std::unique_ptr<Card>> &&cards, bool alternate_suits, RankOrder order)
        : CardContainer(std::move(cards)), alternate_suits(alternate_suits), order(order) {

}

TableauStack::TableauStack(TableauStack &&stack, bool alternate_suits)
        : CardContainer(std::move(stack.cards)), alternate_suits(alternate_suits), order(stack.order) {

}

TableauStack::TableauStack(bool alternate_suits, RankOrder order)
        : alternate_suits(alternate_suits), order(order) {

}

bool TableauStack::push_back(TableauStack &&stack) {
    if (is_suitable(stack)) {
        for (auto &c : stack.cards) {
            this->cards.push_back(std::move(c));
        }
        return true;
    }
    return false;
}

bool TableauStack::is_suitable(const Card *card) const {
    const Card *top = peek_card();
    if (card == nullptr) {
        return true;
    }
    bool ascending = order == RankOrder::Ascending;
    if (top == nullptr) {
        return card->get_rank() == (ascending ? Card::eRank::Ace : Card::eRank::King);
    }
    int inc = ascending ? 1 : -1;
    return (static_cast<int>(card->get_rank()) == static_cast<int>(top->get_rank()) + inc)
           && (alternate_suits ^ (top->is_black() == card->is_black()));
}

bool TableauStack::is_suitable(const std::vector<const Card *> &stack) {
    bool ascending = order == RankOrder::Ascending;
    if (cards.size() == 0) {
        return stack.size() == 0 ||
               stack[0]->get_rank() == (ascending ? Card::eRank::Ace : Card::eRank::King);
    }
    bool last_is_black = cards.back().get()->is_black();
    int last_rank = static_cast<int>(cards.back().get()->get_rank());
    int inc = ascending ? 1 : -1;
    for (const auto i : stack) {
        bool cur_is_black = i->is_black();
        int cur_rank = static_cast<int>(i->get_rank());
        // FIXME: one func(prev, next)
        if ((alternate_suits ^ (last_is_black != cur_is_black)) || cur_rank != last_rank + inc) {
            return false;
        } else {
            last_is_black = cur_is_black;
            last_rank = cur_rank;
        }
    }
    return true;
}

void TableauStack::pop_tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    for (size_t i = 0; i < amount; ++i) {
        cards.pop_back();
    }
    if (!cards.empty()) {
        cards.back()->set_side(Card::eSide::Face);
    }
}

void TableauStack::pop_back() {
    CardContainer::pop_back();
    if (!cards.empty()) {
        cards.back()->set_side(Card::eSide::Face);
    }
}

TableauStack TableauStack::get_tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    std::vector<std::unique_ptr<Card>> tale;
    for (auto i = cards.end() - amount; i < cards.end(); ++i) {
        tale.push_back(std::move(*i));
    }
    pop_tale(amount);
    return std::move(TableauStack(std::move(tale), alternate_suits));
}

TableauStack &TableauStack::operator=(TableauStack &&that) {
    if (this != &that) {
        this->cards = std::move(that.cards);
        alternate_suits = that.alternate_suits;
        order = that.order;
    }
    return *this;
}

const std::vector<const Card *> TableauStack::peek_tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    std::vector<const Card *> tale;
    for (auto i = cards.end() - amount; i < cards.end(); ++i) {
        tale.push_back(i->get());
    }
    return tale;
}

bool TableauStack::is_suitable(const TableauStack &stack) {
    return stack.cards.size() == 0 || is_suitable(stack.cards[0].get());
}

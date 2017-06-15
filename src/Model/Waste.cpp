//
// Created by moonlightnvkz on 07.05.17.
//

#include "include/Model/Waste.h"
#include "include/Model/CardDeck.h"

void Waste::move_cards_to_deck() {
    std::vector<std::unique_ptr<Card>> res{std::make_move_iterator(cards.rbegin()),
                                           std::make_move_iterator(cards.rend())};
    cards.clear();
    deck->push_back(std::move(res));
}

bool Waste::push_back(std::unique_ptr<Card> &&card) {
    if (card == nullptr) {
        return true;
    }
    if (!CardContainer::push_back(std::move(card))) {
        return false;
    }
    cards.back()->set_side(eSide::Face);
    return true;
}

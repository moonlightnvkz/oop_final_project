//
// Created by moonlightnvkz on 07.05.17.
//

#include <cassert>
#include <stdexcept>
#include <algorithm>
#include "include/Settings.h"
#include "include/Model/CardDeck.h"
#include "include/Model/Waste.h"

CardDeck::CardDeck()
        : waste(nullptr) {
    for (unsigned i = 0; i < Amount; ++i) {
        cards.push_back(std::make_unique<Card>(static_cast<eSuit>(i / CPS),
                                               static_cast<eRank>(i % CPS)));
    }
    std::srand(static_cast<unsigned>(time(nullptr)));
    auto random_int = [] (int i) { return std::rand() % i; };
    std::random_shuffle(cards.begin(), cards.end(), random_int);
}

void CardDeck::move_card_to_waste() {
    assert(waste != nullptr);
    std::unique_ptr<Card> top = get_back();
    waste->push_back(std::move(top));
}

bool CardDeck::push_back(std::unique_ptr<Card> &&card) {
    if (card == nullptr) {
        return true;
    }
    if (!CardContainer::push_back(std::move(card))) {
        return false;
    }
    cards.back()->set_side(eSide::Back);
    return true;
}

void CardDeck::push_back(std::vector<std::unique_ptr<Card>> &&cards) {
    auto old_end = this->cards.end();
    this->cards.insert(old_end,
                       std::make_move_iterator(cards.begin()),
                       std::make_move_iterator(cards.end()));
    for (auto i = old_end; i < this->cards.end(); ++i) {
        i->get()->set_side(eSide::Back);
    }
    cards.clear();
}

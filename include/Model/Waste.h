//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include "CardContainer.h"

class CardDeck;

class Waste : public CardContainer{
public:
    Waste(CardDeck *deck) : deck(deck) {};

    ~Waste() { };

    void move_cards_to_deck();

    virtual bool push_back(std::unique_ptr<Card> &&card) override;

private:
    CardDeck *deck;
};



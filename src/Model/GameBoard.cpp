//
// Created by moonlightnvkz on 10.06.17.
//

#include "include/Settings.h"
#include "include/Model/GameBoard.h"
#include "include/Model/CardDeck.h"
#include "include/Model/Waste.h"
#include "include/Model/Foundation.h"
#include "include/Model/Tableau.h"

GameBoard::GameBoard() {
    load_model();
}

GameBoard::~GameBoard() {
    delete_model();
}

void GameBoard::restart() {
    delete_model();
    load_model();
}

void GameBoard::load_model() {
    const Settings::GameRules &game_rules = Settings::GetInstance().game_rules;
    deck = new CardDeck;
    waste = new Waste(deck);
    deck->set_waste(waste);
    foundation = new Foundation;
    std::vector<TableauStack> tableau_stacks;
    size_t stacks_amount = game_rules.tableau_stacks_amount;
    for (size_t i = 0; i < stacks_amount; ++i) {
        size_t cards_amount = i + 1;
        std::vector<std::unique_ptr<Card>> cards;
        for (size_t j = 0; j < cards_amount; ++j) {
            cards.push_back(deck->get_back());
        }
        TableauStack stack(std::move(cards), game_rules.alternate_suits_in_the_tableau,
                           game_rules.tableau_rank_order);
        tableau_stacks.push_back(std::move(stack));
    }
    tableau = new Tableau(std::move(tableau_stacks));
}

void GameBoard::delete_model() {
    delete waste;
    delete deck;
    delete foundation;
    delete tableau;
}

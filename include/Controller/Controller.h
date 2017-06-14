//
// Created by moonlightnvkz on 26.05.17.
//

#pragma once
#include <utility>
#include <cstddef>

class GameBoardView;
class GameBoard;

class Controller {
public:
    Controller(GameBoard *model, GameBoardView *view);

    void turn_deck();

    void card_from_waste_is_taken();

    void card_from_foundation_is_taken(unsigned i);

    void tableau_stack_tale_is_taken(unsigned i, size_t amount);

    bool put_to_tableau_stack(unsigned j);

    bool put_to_foundation_stack(unsigned j);

    void release_back();

    void restart_game();

protected:
    enum class Origin {
        None,
        Waste,
        Tableau,
        Foundation
    } origin;

    /// Need for taking from stack <i, amount>
    std::pair<unsigned, size_t> origin_descr;

    void sync_view_with_model();

    GameBoardView *view;

    GameBoard *model;
};



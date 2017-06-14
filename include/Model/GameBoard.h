//
// Created by moonlightnvkz on 10.06.17.
//

#pragma once

class CardDeck;
class Waste;
class Foundation;
class Tableau;

class GameBoard {
public:
    GameBoard();

    virtual ~GameBoard();

    void restart();

    CardDeck *deck;

    Waste *waste;

    Foundation *foundation;

    Tableau *tableau;

protected:
    void load_model();

    void delete_model();
};



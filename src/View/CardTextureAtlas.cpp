//
// Created by moonlightnvkz on 30.05.17.
//

#include <include/Model/CardDeck.h>
#include <include/View/TextureManager.h>
#include <cassert>
#include "include/View/CardTextureAtlas.h"

CardTextureAtlas::CardTextureAtlas()
        : textures_loaded(false){

}

CardTextureAtlas &CardTextureAtlas::GetInstance() {
    static CardTextureAtlas atlas;
    return atlas;
}

std::string CardTextureAtlas::get_face_texture_name(Card::eSuit suit, Card::eRank rank) const {
    std::string name = "res/";
    switch(suit) {
        case Card::eSuit::Hearts: {
            name += "heart";
            break;
        }
        case Card::eSuit::Clubs: {
            name += "club";
            break;
        }
        case Card::eSuit::Diamonds: {
            name += "diamond";
            break;
        }
        case Card::eSuit::Spades: {
            name += "spade";
            break;
        }
    }
    switch(rank) {
        case Card::eRank::Ace: {
            name += "Ace";
            break;
        }
        case Card::eRank::Two: {
            name += "2";
            break;
        }
        case Card::eRank::Three: {
            name += "3";
            break;
        }
        case Card::eRank::Four: {
            name += "4";
            break;
        }
        case Card::eRank::Five: {
            name += "5";
            break;
        }
        case Card::eRank::Six: {
            name += "6";
            break;
        }
        case Card::eRank::Seven: {
            name += "7";
            break;
        }
        case Card::eRank::Eight: {
            name += "8";
            break;
        }
        case Card::eRank::Nine: {
            name += "9";
            break;
        }
        case Card::eRank::Ten: {
            name += "10";
            break;
        }
        case Card::eRank::Jack: {
            name += "Jack";
            break;
        }
        case Card::eRank::Queen: {
            name += "Queen";
            break;
        }
        case Card::eRank::King: {
            name += "King";
            break;
        }
    }
    name += ".png";
    return name;
}

void CardTextureAtlas::load_textures() {
    TextureManager &manager = TextureManager::GetInstance();
    // 52 - amount -- cut off cards with small ranks
    for (unsigned i = 0; i < CardDeck::Amount; ++i) {
        ids.push_back(manager.load(get_face_texture_name(static_cast<Card::eSuit>(i / CardDeck::CPS),
                                                         static_cast<Card::eRank>(i % CardDeck::CPS))));
    }
    ids.push_back(manager.load("res/blueBack.png"));
    textures_loaded = true;
}

const QPixmap &CardTextureAtlas::get_texture(Card::eSuit suit, Card::eSide side, Card::eRank rank) {
    assert(textures_loaded);
    TextureManager &manager = TextureManager::GetInstance();
    if (side == Card::eSide::Back) {
        return manager.get_by_id(ids.back());
    } else {
        return manager.get_by_id(ids.at(
                static_cast<unsigned>(suit) * CardDeck::CPS + static_cast<unsigned>(rank))
        );
    }
}
//
// Created by moonlightnvkz on 30.05.17.
//

#include <cassert>
#include "include/View/TextureManager.h"
#include "include/Model/CardDeck.h"
#include "include/View/CardTextureAtlas.h"

CardTextureAtlas::CardTextureAtlas()
        : textures_loaded(false){

}

CardTextureAtlas &CardTextureAtlas::GetInstance() {
    static CardTextureAtlas atlas;
    return atlas;
}

std::string CardTextureAtlas::get_face_texture_name(eSuit suit, eRank rank) const {
    std::string name = "res/";
    switch(suit) {
        case eSuit::Hearts: {
            name += "heart";
            break;
        }
        case eSuit::Clubs: {
            name += "club";
            break;
        }
        case eSuit::Diamonds: {
            name += "diamond";
            break;
        }
        case eSuit::Spades: {
            name += "spade";
            break;
        }
    }
    switch(rank) {
        case eRank::Ace: {
            name += "Ace";
            break;
        }
        case eRank::Two: {
            name += "2";
            break;
        }
        case eRank::Three: {
            name += "3";
            break;
        }
        case eRank::Four: {
            name += "4";
            break;
        }
        case eRank::Five: {
            name += "5";
            break;
        }
        case eRank::Six: {
            name += "6";
            break;
        }
        case eRank::Seven: {
            name += "7";
            break;
        }
        case eRank::Eight: {
            name += "8";
            break;
        }
        case eRank::Nine: {
            name += "9";
            break;
        }
        case eRank::Ten: {
            name += "10";
            break;
        }
        case eRank::Jack: {
            name += "Jack";
            break;
        }
        case eRank::Queen: {
            name += "Queen";
            break;
        }
        case eRank::King: {
            name += "King";
            break;
        }
    }
    name += ".png";
    return name;
}

void CardTextureAtlas::load_textures() {
    TextureManager &manager = TextureManager::GetInstance();
    for (unsigned i = 0; i < CardDeck::Amount; ++i) {
        ids.push_back(manager.load(get_face_texture_name(static_cast<eSuit>(i / CardDeck::CPS),
                                                         static_cast<eRank>(i % CardDeck::CPS))));
    }
    ids.push_back(manager.load("res/blueBack.png"));
    textures_loaded = true;
}

const QPixmap &CardTextureAtlas::get_texture(eSuit suit, eSide side, eRank rank) const {
    assert(textures_loaded);
    TextureManager &manager = TextureManager::GetInstance();
    if (side == eSide::Back) {
        return manager.get_by_id(ids.back());
    } else {
        return manager.get_by_id(ids.at(
                static_cast<unsigned>(suit) * CardDeck::CPS + static_cast<unsigned>(rank))
        );
    }
}
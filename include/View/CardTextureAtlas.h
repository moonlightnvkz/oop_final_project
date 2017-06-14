//
// Created by moonlightnvkz on 30.05.17.
//

#pragma once

#include <string>
#include <QtGui/QPixmap>
#include "include/Model/Card.h"

class CardTextureAtlas {
public:
    static CardTextureAtlas &GetInstance();

    CardTextureAtlas(const CardTextureAtlas &) = delete;

    CardTextureAtlas &operator=(const CardTextureAtlas &) = delete;

    void load_textures();

    const QPixmap &get_texture(Card::eSuit suit, Card::eSide side, Card::eRank rank);

private:
    CardTextureAtlas();

    std::string get_face_texture_name(Card::eSuit suit, Card::eRank rank) const;

    std::vector<unsigned> ids;

    bool textures_loaded;
};



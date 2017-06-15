//
// Created by moonlightnvkz on 29.05.17.
//

#pragma once

#include <string>
#include <vector>

class QPixmap;

class TextureManager {
public:
    static TextureManager &GetInstance();

    TextureManager(const TextureManager &) = delete;

    TextureManager &operator=(const TextureManager &) = delete;

    TextureManager(TextureManager &&) = delete;

    TextureManager &operator=(TextureManager &&) = delete;

    virtual ~TextureManager() {};

    unsigned load(const std::string filename);

    const QPixmap &get_by_id(const unsigned id) const;

private:
    TextureManager();

    std::vector<QPixmap> pixmaps;

    QPixmap load_default_texture(const char *filename);
};



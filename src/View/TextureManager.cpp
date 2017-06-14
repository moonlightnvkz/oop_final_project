//
// Created by moonlightnvkz on 29.05.17.
//

#include <cassert>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include "include/View/TextureManager.h"

TextureManager &TextureManager::GetInstance() {
    static TextureManager manager;
    return manager;
}

TextureManager::TextureManager() {

}

unsigned TextureManager::load(const std::string filename) {
    QPixmap pmap(filename.c_str());
    if (pmap.isNull()) {
        pmap = load_default_texture(filename.c_str());
    }
    pixmaps.push_back(pmap);
    return static_cast<unsigned>(pixmaps.size() - 1);
}

const QPixmap &TextureManager::get_by_id(unsigned id) {
    assert(id < pixmaps.size());
    return pixmaps[id];
}

QPixmap TextureManager::load_default_texture(const char *filename) {
    constexpr const int W = 500;
    constexpr const int H = 500;
    constexpr const int Size = 25;
    QPixmap pmap(W, H);
    QPainter painter(&pmap);
    for (int i = 0; i < W; i += Size) {
        for (int j = 0; j < H; j += Size) {
            int nw = i / Size;  // Horizontal number
            int nh = j / Size;  // Vertical number
            if (nw % 2 == nh % 2) {
                painter.fillRect(i, j, i + Size, j + Size, Qt::GlobalColor::darkMagenta);
            } else {
                painter.fillRect(i, j, i + Size, j + Size, Qt::GlobalColor::black);
            }
        }
    }
    painter.setPen(Qt::GlobalColor::white);
    QFont font;
    font.setPixelSize(W / 20);
    painter.setFont(font);
    painter.drawText(0, 0, W, H, Qt::AlignCenter, filename);
    return pmap;
}
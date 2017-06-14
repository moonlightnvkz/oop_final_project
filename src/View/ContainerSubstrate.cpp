//
// Created by moonlightnvkz on 10.06.17.
//

#include <QDebug>
#include <include/View/TextureManager.h>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QCoreApplication>
#include "include/View/ContainerSubstrate.h"

ContainerSubstrate::ContainerSubstrate(QGraphicsItem *parent)
        : QGraphicsPixmapItem(parent) {
    TextureManager &tm = TextureManager::GetInstance();
    static unsigned bg = tm.load("res/stackBg.png");
    setPixmap(tm.get_by_id(bg));
}

ContainerSubstrate::~ContainerSubstrate() {

}

void ContainerSubstrate::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "substrate" << parentObject();
    QCoreApplication::sendEvent(parentObject(), event); // FIXME: emit signal
}

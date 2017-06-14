//
// Created by moonlightnvkz on 10.06.17.
//

#pragma once


#include <QtWidgets/QGraphicsPixmapItem>

class ContainerSubstrate : public QGraphicsPixmapItem {
public:
    explicit ContainerSubstrate(QGraphicsItem *parent);

    virtual ~ContainerSubstrate() override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};



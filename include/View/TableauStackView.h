//
// Created by moonlightnvkz on 29.05.17.
//

#pragma once

#include "CardContainerView.h"

class TableauStack;

class TableauStackView : public CardContainerView {
    Q_OBJECT
public:
    explicit TableauStackView(const CardContainer &container,
                              QGraphicsItem *parent = nullptr, int v_shift = 15);

    virtual ~TableauStackView() override;

    virtual void update(const CardContainer &container) override;

    virtual QRectF boundingRect() const override;

public slots:
    void adjust_v_shift(int new_v_shift);

protected:
    virtual QPixmap create_pixmap_for_drag(size_t amount) override;

    int v_shift;
};



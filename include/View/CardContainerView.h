// Created by moonlightnvkz on 29.05.17.
//
#pragma once

#include <QtWidgets/QGraphicsObject>

class CardContainer;
class ContainerSubstrate;
class CardView;

class CardContainerView : public QGraphicsObject {
    Q_OBJECT
public:
    explicit CardContainerView(const CardContainer &container, QGraphicsItem *parent = nullptr);

    explicit CardContainerView(QGraphicsItem *parent = nullptr);

    virtual ~CardContainerView() override;

    virtual QRectF boundingRect() const override;

    virtual void update(const CardContainer &container);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void mouse_pressed();

    void drag_happen(size_t amount);

    void card_dropped();

    void drag_release_back();

public slots:
    void on_card_mouse_pressed();

    void on_card_drag_happen();

protected:
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;

    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;

    virtual void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QObject *drag_processing(const QPixmap &pmap, const QRectF boundingRect);

    virtual QPixmap create_pixmap_for_drag(const size_t amount) const;

    std::vector<CardView *> cards;

    static unsigned background;

    static bool background_loaded;
};


//
// Created by moonlightnvkz on 29.05.17.
//

#pragma once

#include <vector>
#include <QObject>
#include <QtWidgets/QGraphicsItemGroup>

class CardContainerView;
class CardContainer;

class StackLayoutSignalsSlots : public QObject {
    Q_OBJECT
public:
signals:
    void card_dropped(const unsigned i);

    void tale_taken(const unsigned i, const size_t amount);

    void drag_release_back();
public slots:
    virtual void on_card_dropped() = 0;

    virtual void on_drag_happen(const size_t amount) = 0;

    virtual void on_drag_release_back() = 0;

    virtual void adjust_h_space(const int new_h_space) = 0;
};

template<typename T>
class StackLayoutView : public StackLayoutSignalsSlots, public QGraphicsItemGroup {
public:
    explicit StackLayoutView(const int h_space = 0, QGraphicsItem *parent = nullptr);

    explicit StackLayoutView(const std::vector<std::reference_wrapper<const CardContainer>> &stacks,
                             const int h_space = 0, QGraphicsItem *parent = nullptr);

    virtual ~StackLayoutView() override;

    void load_stacks(const std::vector<std::reference_wrapper<const CardContainer>> &stacks);

    void update(const CardContainer &stack, const unsigned i);

    virtual QRectF boundingRect() const override;

    // Slots
    virtual void on_card_dropped() override;

    virtual void adjust_h_space(const int new_h_space) override;

    virtual void on_drag_happen(const size_t amount) override;

    virtual void on_drag_release_back() override;

    const std::vector<T*> get_stacks() const { return stacks; }
protected:
    int h_space;

    unsigned get_stack_idx(const void *p);

    std::vector<T*> stacks;
};



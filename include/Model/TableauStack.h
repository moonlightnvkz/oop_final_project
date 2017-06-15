//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once


#include "include/Settings.h"
#include "CardContainer.h"

using RankOrder = Settings::GameRules::RankOrder;

class TableauStack : public CardContainer{
public:
    explicit TableauStack(bool alternate_suits = true, RankOrder order = RankOrder::Descending);

    TableauStack(TableauStack &&stack, bool alternate_suits = true);

    TableauStack(std::vector<std::unique_ptr<Card>> &&cards,
                 bool alternate_suits = true, RankOrder order = RankOrder::Descending);

    ~TableauStack() { };

    using CardContainer::push_back;

    bool push_back(TableauStack &&stack);

    TableauStack get_tale(size_t amount);

    const std::vector<const Card*> peek_tale(size_t amount);

    virtual bool is_suitable(const Card *card) const override;

    virtual bool is_suitable(const std::vector<const Card *> &stack) const;

    virtual bool is_suitable(const TableauStack &stack) const;

    TableauStack &operator=(TableauStack &&that);

private:
    virtual void pop_back() override;

    void pop_tale(size_t amount);

    bool alternate_suits;

    RankOrder order;
};
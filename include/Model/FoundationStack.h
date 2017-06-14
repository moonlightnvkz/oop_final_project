//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include <vector>
#include "include/Settings.h"
#include "CardContainer.h"

using RankOrder = Settings::GameRules::RankOrder;

class FoundationStack : public CardContainer{
public:
    FoundationStack (RankOrder order = RankOrder::Ascending);

    FoundationStack (FoundationStack  &&stack);

    FoundationStack &operator=(FoundationStack &&that);

    ~FoundationStack() { };

    virtual bool is_suitable(const Card *card) const override;

protected:
    RankOrder order;
};



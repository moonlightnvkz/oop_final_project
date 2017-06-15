//
// Created by moonlightnvkz on 07.05.17.
//

#include "include/Model/Foundation.h"

bool Foundation::is_complete() const {
    for(const auto &stack : stacks) {
        const Card *card = stack.peek_card();
        if (card == nullptr || card->get_rank() != eRank::King) {
            return false;
        }
    }
    return true;
}

Foundation &Foundation::operator=(Foundation &&that) {
    if (this != &that) {
        this->stacks = std::move(that.stacks);
    }
    return *this;
}

Foundation::Foundation() {
    Settings &settings = Settings::GetInstance();
    for (unsigned i = 0; i < Amount; ++i) {
        stacks.push_back(FoundationStack(settings.game_rules.foundation_rank_order));
    }
}

//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include "FoundationStack.h"

class Foundation {
public:
    Foundation();

    Foundation(Foundation &&foundation) : stacks(std::move(foundation.stacks)) { }

    FoundationStack &get_stack(const size_t i) { return stacks.at(i); }

    virtual ~Foundation() { }

    const std::vector<FoundationStack> &peek_stacks() const { return stacks; }

    bool is_complete() const;

    Foundation &operator=(Foundation &&that);

private:
    static constexpr const unsigned Amount = 4;

    std::vector<FoundationStack> stacks;
};



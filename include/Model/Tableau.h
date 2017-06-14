//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <array>
#include "TableauStack.h"

class Tableau {
public:
    Tableau(unsigned stacks_amount);

    virtual ~Tableau() { }

    Tableau(Tableau &&tableau) : stacks(std::move(tableau.stacks)) { }

    Tableau(std::vector<TableauStack> &&stacks) : stacks(std::move(stacks)){ }

    TableauStack &get_stack(size_t i) { return stacks.at(i); }

    const std::vector<TableauStack> &peek_stacks() const { return stacks; }

    Tableau &operator=(Tableau &&that);

private:
    std::vector<TableauStack> stacks;
};

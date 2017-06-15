//
// Created by moonlightnvkz on 15.05.17.
//

#include "include/Model/Tableau.h"

Tableau &Tableau::operator=(Tableau &&that) {
    if (this != &that) {
        this->stacks = std::move(that.stacks);
    }
    return *this;
}

Tableau::Tableau(const unsigned stacks_amount)
        : stacks(stacks_amount) {
}

//
// Created by moonlightnvkz on 11.06.17.
//
#include <istream>
#include "include/Settings.h"

Settings::Settings() {
    load_default();
}

Settings &Settings::GetInstance() {
    static Settings settings;
    return settings;
}

void Settings::load_default() {
    this->appearance.foundation_spacing = 0;
    this->appearance.tableau_spacing = 5;
    this->appearance.tableau_shift = 15;
    this->appearance.background_color = {24, 134, 45};

    this->game_rules.tableau_stacks_amount = 7;
    this->game_rules.alternate_suits_in_the_tableau = true;
    this->game_rules.tableau_rank_order = Settings::GameRules::RankOrder::Descending;
    this->game_rules.foundation_rank_order = Settings::GameRules::RankOrder::Ascending;
}

std::ostream &operator<<(std::ostream &os, const Settings::GameRules::RankOrder order) {
    return os << static_cast<int>(order);
}

std::istream &operator>>(std::istream &is, Settings::GameRules::RankOrder &order) {
    int o;
    is >> o;
    order = static_cast<Settings::GameRules::RankOrder>(o);
    return is;
}

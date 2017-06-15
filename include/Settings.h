//
// Created by moonlightnvkz on 11.06.17.
//

#pragma once


#include <ostream>

class Settings {
public:

    static Settings &GetInstance();

    Settings(const Settings &) = delete;

    Settings(Settings &&) = delete;

    Settings &operator=(const Settings &) = delete;

    Settings &operator=(Settings &&) = delete;

    void load_default();

    struct Appearance {
        int foundation_spacing;

        int tableau_spacing;

        int tableau_shift;

        struct Color {
            int red;
            int green;
            int blue;
        } background_color;
    } appearance;

    struct GameRules {
        enum class RankOrder {
            Ascending,
            Descending
        };

        unsigned tableau_stacks_amount;

        bool alternate_suits_in_the_tableau;

        RankOrder tableau_rank_order;

        RankOrder foundation_rank_order;
    } game_rules;

private:
    Settings();
};

std::ostream &operator<<(std::ostream &os, const Settings::GameRules::RankOrder order);

std::istream &operator>>(std::istream &is, Settings::GameRules::RankOrder &order);
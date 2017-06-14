//
// Created by moonlightnvkz on 13.06.17.
//

#include "include/SettingsReader.h"
#include "include/Settings.h"

bool SettingsReader::read(std::istream &is) {
    Settings &settings = Settings::GetInstance();
    is >> settings.appearance.foundation_spacing
       >> settings.appearance.tableau_spacing
       >> settings.appearance.tableau_shift
       >> settings.appearance.background_color.red
       >> settings.appearance.background_color.green
       >> settings.appearance.background_color.blue;
    is >> settings.game_rules.tableau_stacks_amount
       >> settings.game_rules.alternate_suits_in_the_tableau
       >> settings.game_rules.tableau_rank_order
       >> settings.game_rules.foundation_rank_order;
    return !is.fail();
}

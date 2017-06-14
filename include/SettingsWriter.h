//
// Created by moonlightnvkz on 13.06.17.
//

#pragma once
#include <ostream>

class SettingsWriter {
public:
    SettingsWriter() = delete;

    static bool write(std::ostream &os);
};



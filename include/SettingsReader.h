//
// Created by moonlightnvkz on 13.06.17.
//

#pragma once


#include <istream>

class SettingsReader {
public:
    SettingsReader() = delete;

    static bool read(std::istream &is);
};



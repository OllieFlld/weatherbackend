//
// Created by Oliver Field on 28/10/2025.
//

#include "DatabaseHelper.h"


std::unordered_map<char, char> formatQueryToMap(char** data, char** columns) {
    std::unordered_map<char, char> formatted;

    for (int i = 0; i < sizeof(columns); i++) {
        formatted[*columns[i]] = *data[i];
    }

    return formatted;
}
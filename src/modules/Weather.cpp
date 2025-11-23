//
// Created by Oliver Field on 23/11/2025.
//

#include "Weather.h"
using namespace Modules;

Weather::Weather(DatabaseManager &database) {
    this->database = &database;
    functions["getCurrentTemp"] = [&]()->std::string{return this->getCurrentTemp();};
}

std::string Weather::getCurrentTemp() {
    return database->getCurrentConditions().air_temp;
}





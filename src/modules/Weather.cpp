//
// Created by Oliver Field on 23/11/2025.
//

#include "Weather.h"
using namespace Modules;

Weather::Weather(DatabaseManager &database) {
    this->database = &database;
    functions["getCurrentTemp"] = [&]()->std::string{return this->getCurrentTemp();};
    functions["getCurrentFeelsLikeTemp"] = [&]()->std::string{return this->getCurrentFeelsLikeTemp();};
    functions["getTodaysPrecip"] = [&]()->std::string{return this->getTodaysPrecip();};
}

std::string Weather::getCurrentTemp() {
    return formatTemp(database->getCurrentConditions().air_temp);
}


std::string Weather::getCurrentFeelsLikeTemp() {
    return "Feels Like: " + formatTemp(database->getCurrentConditions().feels_like);

}

std::string Weather::getTodaysPrecip() {
    return std::format("{:.2f}" , database->getCurrentConditions().local_day_precip_accumulation).append("mm");
}


std::string Weather::formatTemp(double temp) {
    return std::format("{:.1f}" , temp).append("\xB0").append("C");
}



//
// Created by Oliver Field on 22/11/2025.
//

#include "DateTime.h"

#include <format>
#include <chrono>
using namespace Modules;

std::string DateTime::getCurrentDate() {
    auto time = std::chrono::system_clock::now();

    return std::format("({:%Y-%m-%d})", time);
}

DateTime::DateTime() {
    functions["getCurrentDate"] = [&]()->std::string{return this->getCurrentDate();};
}



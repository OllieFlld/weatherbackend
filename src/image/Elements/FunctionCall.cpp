//
// Created by Oliver Field on 22/11/2025.
//

#include "FunctionCall.h"

#include <map>
using namespace Scenes::Elements;

FunctionCall FunctionCall::fromJson(crow::json::rvalue json, std::map<std::string, std::map<std::string, std::function<std::string()>>> allFunctions) {
    FunctionCall functionCall(json["x"].i(), json["y"].i(), json["width"].i(), json["height"].i(), json["fontsize"].i());

    std::string module = json["module"].s();
    std::string function = json["function"].s();
    if (!allFunctions.contains(module)) {
        throw std::invalid_argument("Module " + module + " does not exist");
    }

    if (!allFunctions[module].contains(function)) {
        throw std::invalid_argument("Function " + function + " in module " + module + " does not exist");
    }

    functionCall.function = allFunctions[json["module"].s()][json["function"].s()];

    return functionCall;
}

std::string FunctionCall::callFunction() {
    return function();
}


FunctionCall::FunctionCall(int x, int y, int width, int height, int fontSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->fontSize = fontSize;
}




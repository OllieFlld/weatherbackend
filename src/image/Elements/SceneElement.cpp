//
// Created by Oliver Field on 09/11/2025.
//

#include "SceneElement.h"

SceneElement::SceneElement(int x, int y, int width, int height, std::string value) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->value = value;

}

SceneElement SceneElement::fromJson(crow::json::rvalue json) {
    return SceneElement(json["x"].i(), json["y"].i(), json["width"].i(), json["height"].i(), json["value"].s());
}
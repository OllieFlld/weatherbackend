//
// Created by Oliver Field on 09/11/2025.
//

#include "Base.h"
using namespace Scenes::Elements;

Base::Base(int x, int y, int width, int height, std::string value, int fontSize) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->value = value;
    this->fontSize = fontSize;
}

Base::Base() {

}


Base Base::fromJson(crow::json::rvalue json) {
    return Base(json["x"].i(), json["y"].i(), json["width"].i(), json["height"].i(), json["value"].s(), json["fontsize"].i());
}

//
// Created by Oliver Field on 09/11/2025.
//

#ifndef BACKEND_SCENEELEMENT_H
#define BACKEND_SCENEELEMENT_H
#include <string>
#include <crow/json.h>


class SceneElement {
public:
    SceneElement(int x, int y, int width, int height, std::string name);

    int x;
    int y;
    int width;
    int height;
    std::string value;

    static SceneElement fromJson(crow::json::rvalue);
};


#endif //BACKEND_SCENEELEMENT_H
//
// Created by Oliver Field on 09/11/2025.
//

#ifndef BACKEND_SCENEELEMENT_H
#define BACKEND_SCENEELEMENT_H
#include <string>
#include <crow/json.h>

namespace Scenes::Elements {
    class Base {
    public:
        Base(int x, int y, int width, int height, std::string name, int fontSize);
        Base();

        int x;
        int y;
        int width;
        int height;
        std::string value;
        int fontSize;

        static Base fromJson(crow::json::rvalue);
    };
}


#endif //BACKEND_SCENEELEMENT_H
//
// Created by Oliver Field on 09/11/2025.
//

#ifndef BACKEND_SCENE_H
#define BACKEND_SCENE_H
#include <cimg.h>
#include <list>
#include <map>
#include <crow/json.h>

#include "Elements/Base.h"
#include "Elements/FunctionCall.h"


namespace Scenes {
    class Scene {
    public:
        Scene(int width, int height);
        static Scene fromFile(std::string filename,  std::map<std::string, std::map<std::string, std::function<std::string()>>> allFunctions);
        cimg_library::CImg<unsigned char> draw();
        ///void writeToFile(std::string filename);
        void setElements(std::list<Elements::Base> elements);
        void addElement(Elements::Base element);
        void addFunctionCall(Elements::FunctionCall element);

    private:
        std::list<Elements::Base> elements;
        std::list<Elements::FunctionCall> functionCallElements;
        int width, height;
        int backgroundColour;
        static int scaleDimension(int dimension, int limit);
        static void validateFields(const crow::json::rvalue &json, const std::list<std::string>& validFields);
    };
}


#endif //BACKEND_SCENE_H

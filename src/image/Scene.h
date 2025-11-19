//
// Created by Oliver Field on 09/11/2025.
//

#ifndef BACKEND_SCENE_H
#define BACKEND_SCENE_H
#include <cimg.h>
#include <list>
#include <crow/json.h>

#include "Elements/SceneElement.h"


class SceneElement;

class Scene {
public:
    Scene(int width, int height);
    static Scene fromFile(std::string filename);
    cimg_library::CImg<unsigned char> draw();
    ///void writeToFile(std::string filename);
    void setElements(std::list<SceneElement> elements);
    void addElement(SceneElement element);

private:
    std::list<SceneElement> elements;
    int width, height;
    static int scaleDimension(int dimension, int limit);
    static void validateFields(const crow::json::rvalue &json, const std::list<std::string>& validFields);
};


#endif //BACKEND_SCENE_H

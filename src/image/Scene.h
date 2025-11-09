//
// Created by Oliver Field on 09/11/2025.
//

#ifndef BACKEND_SCENE_H
#define BACKEND_SCENE_H
#include <list>

#include "SceneElement.h"


class SceneElement;

class Scene {
public:
    Scene();
    ~Scene();
    static Scene fromFile(std::string filename);
    void draw();
    void writeToFile(std::string filename);

private:
    std::list<SceneElement> elements;
    int width, height;
};


#endif //BACKEND_SCENE_H

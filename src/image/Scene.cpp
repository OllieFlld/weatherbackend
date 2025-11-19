//
// Created by Oliver Field on 09/11/2025.
//

#include "Scene.h"

#include <fstream>
#include <utility>
#include <crow/json.h>

Scene::Scene(int width, int height) {
    this->width = width;
    this->height = height;
}

cimg_library::CImg<unsigned char> Scene::draw() {
    cimg_library::CImg<unsigned char> image(this->width, this->height);
    for (SceneElement element: elements) {
        image.draw_text(element.x, element.y,
                        element.value.c_str(), cimg_library::cimg::t_black);
    }

    return image;
}

Scene Scene::fromFile(std::string filename) {
    std::ifstream file(filename.c_str());
    if (file.fail()) {
        throw new std::runtime_error("Unable to open file " + filename);
    }

    std::string fileContentString { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    crow::json::rvalue fileContents = crow::json::load(fileContentString);
    validateFields(fileContents, {"height", "width", "elements"});

    int height = fileContents["height"].i();
    int width = fileContents["width"].i();

    Scene scene = Scene(width, height);
    for (crow::json::rvalue element: fileContents["elements"]) {
        validateFields(element, {"x", "y", "value"});
        scene.addElement(SceneElement::fromJson(element));
    }

    return scene;
}

void Scene::validateFields(const crow::json::rvalue &json, const std::list<std::string>& validFields)
{
    for (const std::string& field: validFields) {
        if (json.has(field)) {
            continue;
        }

        throw new std::runtime_error("Required Field '" + field + "' not found");
    }
}



void Scene::setElements(std::list<SceneElement> elements) {
    this->elements = std::move(elements);
}

void Scene::addElement(SceneElement element) {
    elements.push_back(element);
}



int Scene::scaleDimension(int dimension, int limit) {
    return (dimension * limit) / 100;
}



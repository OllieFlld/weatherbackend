//
// Created by Oliver Field on 09/11/2025.
//

#include "Scene.h"

#include <fstream>
#include <utility>
#include <crow/json.h>

#include "Elements/FunctionCall.h"
using namespace Scenes;

Scene::Scene(int width, int height) {
    this->width = width;
    this->height = height;
}

cimg_library::CImg<unsigned char> Scene::draw() {
    cimg_library::CImg<unsigned char> image(this->width, this->height);

    image.fill(0xFFFFFF);

    for (Elements::Base element: elements) {
        image.draw_text(
            element.x,
            element.y,
            element.value.c_str(),

            cimg_library::cimg::t_black,
            0xFFFFFF,
            1,
            element.fontSize
            );
    }

    for (Elements::FunctionCall element: functionCallElements) {
        image.draw_text(
            element.x,
            element.y,
            element.callFunction().c_str(),

            cimg_library::cimg::t_black,
            0xFFFFFF,
            1,
            element.fontSize
            );
    }

    return image;
}

Scene Scene::fromFile(std::string filename,  std::map<std::string, std::map<std::string, std::function<std::string()>>> allFunctions) {
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
        validateFields(element, {"x", "y"});

        if (element.has("module") && element.has("function")) {
            scene.addFunctionCall(Elements::FunctionCall::fromJson(element, allFunctions));

            continue;
        }
        scene.addElement(Elements::Base::fromJson(element));
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



void Scene::setElements(std::list<Elements::Base> elements) {
    this->elements = std::move(elements);
}

void Scene::addElement(Elements::Base element) {
    elements.push_back(element);
}

void Scene::addFunctionCall(Elements::FunctionCall element) {
    functionCallElements.push_back(element);
}




int Scene::scaleDimension(int dimension, int limit) {
    return (dimension * limit) / 100;
}



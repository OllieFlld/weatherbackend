//
// Created by Oliver Field on 06/11/2025.
//

#include "Writer.h"

#include <cimg.h>

using namespace cimg_library;

std::string Writer::write(std::string path, CImg<> image) {
    CImg<> result = image.save_png(path.c_str());

    return path;
}

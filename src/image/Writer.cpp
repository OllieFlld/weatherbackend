//
// Created by Oliver Field on 06/11/2025.
//

#include "Writer.h"

#include <cimg.h>

using namespace cimg_library;

std::string Writer::write(std::string path, WeatherDataEntity conditions) {
    CImg<unsigned char> img(640,400,1,3);
    img.draw_text(100, 100, reinterpret_cast<const char *>(conditions.air_temp),  cimg::t_black);
    img.save(path.c_str());

    return path;
}

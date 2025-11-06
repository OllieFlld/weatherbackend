//
// Created by Oliver Field on 06/11/2025.
//

#ifndef BACKEND_WRITER_H
#define BACKEND_WRITER_H
#include <string>

#include "../entities/WeatherDataEntity.h"


class Writer {
public:
    std::string static write(std::string path, WeatherDataEntity conditions);
};


#endif //BACKEND_WRITER_H
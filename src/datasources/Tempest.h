//
// Created by Oliver Field on 10/12/2025.
//

#ifndef BACKEND_TEMPEST_H
#define BACKEND_TEMPEST_H
#include "../entities/WeatherDataEntity.h"

namespace DataSources {
    class Tempest {
    public:
        Tempest(int station, std::string token);
        Tempest(int station, std::string token, std::string url);

        WeatherDataEntity getMostRecentConditions();

    private:
        int station;
        std::string token;
        std::string url = "https://swd.weatherflow.com/swd/rest/observations/station/";
    };
}


#endif //BACKEND_TEMPEST_H

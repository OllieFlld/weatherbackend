//
// Created by Oliver Field on 27/10/2025.
//

#ifndef BACKEND_WEATHERDATA_H
#define BACKEND_WEATHERDATA_H
#include <string>


struct  WeatherDataEntity {
public:
    std::string timestamp;
    std::string report_interval;
    std::string air_temp;
    std::string wind_lull;
    std::string wind_avg;
    std::string wind_gust;
    std::string wind_dir;
    std::string station_pressure;
    std::string sea_level_pressure;
    std::string rh;
    std::string uv;
    std::string illuminance;
    std::string solar_radiation;
    std::string precip_accumulation;
    std::string local_day_precip_accumulation;
    std::string precip_type;
    std::string nc_precip_accumulation;
    std::string nc_local_day_precip_accumulation;
    std::string strike_count;
    std::string strike_distance;

    static WeatherDataEntity fromDB(char **data, char **columns);
};


#endif //BACKEND_WEATHERDATA_H

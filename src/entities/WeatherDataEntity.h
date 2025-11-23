//
// Created by Oliver Field on 27/10/2025.
//

#ifndef BACKEND_WEATHERDATA_H
#define BACKEND_WEATHERDATA_H
#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <crow/json.h>


namespace SQLite {
    class Statement;
}

class WeatherDataEntity {
public:
    int timestamp;
    std::string report_interval;
    std::string air_temp;
    std::string wind_lull;
    std::string wind_avg;
    std::string wind_gust;
    std::string wind_dir;
    std::string station_pressure;
    std::string rh;
    std::string uv;
    std::string illuminance;
    std::string solar_radiation;
    std::string precip_accumulation;
    std::string local_day_precip_accumulation;
    std::string precip_type;
    std::string strike_count;
    std::string strike_distance;

    static WeatherDataEntity fromDB(SQLite::Statement &statement);

    crow::json::wvalue toJSON();
};


#endif //BACKEND_WEATHERDATA_H

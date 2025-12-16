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
    double air_temp;
    double feels_like;
    double wind_avg;
    double wind_gust;
    int wind_dir;
    double wind_lull;
    double station_pressure;
    double uv;
    int brightness;
    double precip;
    double precip_accumulation;
    double local_day_precip_accumulation;

    WeatherDataEntity();

    static WeatherDataEntity fromDB(SQLite::Statement &statement);

    static WeatherDataEntity fromJSON(const crow::json::rvalue &json);

    crow::json::wvalue toJSON();
};


#endif //BACKEND_WEATHERDATA_H

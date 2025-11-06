//
// Created by Oliver Field on 27/10/2025.
//

#include "WeatherDataEntity.h"

WeatherDataEntity WeatherDataEntity::fromDB(sqlite3_stmt &stmt) {
    WeatherDataEntity weatherData;
    weatherData.air_temp = sqlite3_column_text(&stmt, 2);
    printf(reinterpret_cast<const char *>(weatherData.air_temp));
    return weatherData;
}

crow::json::wvalue WeatherDataEntity::toJSON() {
    return {
        {
            "AirTemp", air_temp
        }
    };
}

//
// Created by Oliver Field on 27/10/2025.
//

#include "WeatherDataEntity.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/Statement.h>

WeatherDataEntity WeatherDataEntity::fromDB(SQLite::Statement &statement) {
    WeatherDataEntity weatherData;
    weatherData.timestamp = statement.getColumn("Timestamp").getInt64();
    weatherData.report_interval = statement.getColumn("ReportInterval").getString();
    weatherData.air_temp = statement.getColumn("AirTemp").getString();
    weatherData.wind_lull = statement.getColumn("WindLull").getString();
    weatherData.wind_avg = statement.getColumn("WindAvg").getString();
    weatherData.wind_gust = statement.getColumn("WindGust").getString();
    weatherData.wind_dir = statement.getColumn("WindDir").getString();
    weatherData.station_pressure = statement.getColumn("StationPressure").getString();
    weatherData.rh = statement.getColumn("Rh").getString();
    weatherData.uv = statement.getColumn("Uv").getString();
    weatherData.illuminance = statement.getColumn("Illuminance").getString();
    weatherData.solar_radiation = statement.getColumn("SolarRadiation").getString();
    weatherData.precip_accumulation = statement.getColumn("PrecipAccumulation").getString();
    weatherData.local_day_precip_accumulation = statement.getColumn("LocalDayPrecipAccumulation").getString();
    weatherData.precip_type = statement.getColumn("PrecipType").getString();
    weatherData.strike_count = statement.getColumn("StrikeCount").getString();
    weatherData.strike_distance = statement.getColumn("StrikeDistance").getString();

    return weatherData;
}

crow::json::wvalue WeatherDataEntity::toJSON() {
    return {
        {
            "AirTemp", air_temp
        }
    };
}

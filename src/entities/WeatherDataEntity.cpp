//
// Created by Oliver Field on 27/10/2025.
//

#include "WeatherDataEntity.h"

#include <SQLiteCpp/Column.h>
#include <SQLiteCpp/Statement.h>

WeatherDataEntity::WeatherDataEntity() {
    timestamp = 0;
    air_temp = 0;
    feels_like = 0;
    wind_avg = 0;
    wind_gust = 0;
    wind_dir = 0;
    wind_lull = 0;
    station_pressure = 0;
    uv = 0;
    brightness = 0;
    precip = 0;
    precip_accumulation = 0;
    local_day_precip_accumulation = 0;
}

WeatherDataEntity WeatherDataEntity::fromDB(SQLite::Statement &statement) {
    WeatherDataEntity weatherData;
    weatherData.timestamp = statement.getColumn("Timestamp").getInt();
    weatherData.air_temp = statement.getColumn("AirTemp").getDouble();
    weatherData.feels_like = statement.getColumn("FeelsLike").getDouble();
    weatherData.wind_avg = statement.getColumn("WindAvg").getDouble();
    weatherData.wind_gust = statement.getColumn("WindGust").getDouble();
    weatherData.wind_dir = statement.getColumn("WindDir").getInt();
    weatherData.wind_lull = statement.getColumn("WindLull").getDouble();
    weatherData.station_pressure = statement.getColumn("StationPressure").getDouble();
    weatherData.uv = statement.getColumn("Uv").getDouble();
    weatherData.brightness = statement.getColumn("Brightness").getInt();
    weatherData.precip = statement.getColumn("Precip").getDouble();
    weatherData.precip_accumulation = statement.getColumn("PrecipAccumulation").getDouble();
    weatherData.local_day_precip_accumulation = statement.getColumn("LocalDayPrecipAccumulation").getDouble();

    return weatherData;
}

WeatherDataEntity WeatherDataEntity::fromJSON(const crow::json::rvalue &json) {
    WeatherDataEntity weatherData;

    crow::json::rvalue observation = json["obs"][0];

    if (observation.has("timestamp")) {
        weatherData.timestamp = observation["timestamp"].i();
    }

    if (observation.has("air_temperature")) {
        weatherData.air_temp = observation["air_temperature"].d();
    }

    if (observation.has("feels_like")) {
        weatherData.feels_like = observation["feels_like"].d();
    }

    if (observation.has("wind_avg")) {
        weatherData.wind_avg = observation["wind_avg"].d();
    }

    if (observation.has("wind_gust")) {
        weatherData.wind_gust = observation["wind_gust"].d();
    }

    if (observation.has("wind_dir")) {
        weatherData.wind_dir = observation["wind_dir"].i();
    }

    if (observation.has("wind_lull")) {
        weatherData.wind_lull = observation["wind_lull"].d();
    }

    if (observation.has("station_pressure")) {
        weatherData.wind_lull = observation["station_pressure"].d();
    }

    if (observation.has("uv")) {
        weatherData.uv = observation["uv"].d();
    }

    if (observation.has("brightness")) {
        weatherData.brightness = observation["brightness"].i();
    }

    if (observation.has("precip")) {
        weatherData.precip = observation["precip"].d();
    }

    if (observation.has("precip_accumulation")) {
        weatherData.precip_accumulation = observation["precip_accumulation"].d();
    }

    if (observation.has("local_day_precip_accumulation")) {
        weatherData.local_day_precip_accumulation = observation["local_day_precip_accumulation"].d();
    }

    return weatherData;
}


crow::json::wvalue WeatherDataEntity::toJSON() {
    return {
        {
            "AirTemp", air_temp
        }
    };
}

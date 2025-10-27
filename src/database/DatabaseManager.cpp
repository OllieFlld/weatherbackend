//
// Created by Oliver Field on 27/10/2025.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(std::string dbPath) {
    sqlite3_open(dbPath.c_str(), &this->db);
    if (!tablesExist()) {
        createWeatherTable();
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(this->db);
}

bool DatabaseManager::tablesExist() {
    const char *query = "SELECT name FROM sqlite_master WHERE type = 'table' and name = 'weather';";
    bool tableExists = false;
    sqlite3_exec(
        db,
        query,
        [](void *tableExists, int count, char **data, char **columns) {
            *reinterpret_cast<bool *>(tableExists) = true;

            return 1;
        },
        &tableExists,
        nullptr);

    return tableExists;
}

void DatabaseManager::createWeatherTable() {
    const char *sql = "CREATE TABLE weather ("
            "ID INT PRIMARY KEY NOT NULL,"
            "Timestamp INTEGER,"
            "ReportInterval TEXT,"
            "AirTemp TEXT,"
            "WindLull TEXT,"
            "WindAvg TEXT,"
            "WindGust TEXT,"
            "WindDir TEXT,"
            "StationPressure TEXT,"
            "Rh TEXT,"
            "Uv TEXT,"
            "Illuminance TEXT,"
            "SolarRadiation TEXT,"
            "PrecipAccumulation TEXT,"
            "LocalDayPrecipAccumulation TEXT,"
            "PrecipType TEXT,"
            "StrikeCount TEXT,"
            "StrikeDistance TEXT"
            ");";

    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}

WeatherDataEntity DatabaseManager::getCurrentConditions() {
    WeatherDataEntity conditions;

    const char *sql = "SELECT"
            "Timestamp,"
            "ReportInterval,"
            "AirTemp,"
            "WindLull,"
            "WindAvg,"
            "WindGust,"
            "WindDir,"
            "StationPressure,"
            "Rh,"
            "Uv,"
            "Illuminance,"
            "SolarRadiation,"
            "PrecipAccumulation,"
            "LocalDayPrecipAccumulation,"
            "PrecipType,"
            "StrikeCount,"
            "StrikeDistance"
            "FROM Weather"
            "ORDER BY Timestamp DESC"
            "LIMIT 1;";
    sqlite3_exec(db, sql,
        [](void *conditions, int count, char **data, char **columns) {
            *reinterpret_cast<WeatherDataEntity *>(conditions) = WeatherDataEntity::fromDB(data, columns);

            return 1;
    }, &conditions, nullptr);

    return conditions;
}

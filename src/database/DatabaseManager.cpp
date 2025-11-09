//
// Created by Oliver Field on 27/10/2025.
//

#include "DatabaseManager.h"

#include <list>

#include "DatabaseHelper.h"

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


std::list<WeatherDataEntity> DatabaseManager::getRecentConditions(int count = 0) {
    std::string sql = "SELECT"
            " Timestamp,"
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
            " FROM weather"
            " ORDER BY Timestamp DESC";

    if (count > 0) {
        sql = sql + " LIMIT " + std::to_string(count);
    }
    sqlite3_stmt *stmt;

    int prepared = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (prepared != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    std::list<WeatherDataEntity> conditions;

    while ((sqlite3_step(stmt) == SQLITE_ROW)) {
        conditions.push_back(WeatherDataEntity::fromDB(*stmt));
    }

    return conditions;
}

WeatherDataEntity DatabaseManager::getCurrentConditions() {
    return getRecentConditions(1).front();
}



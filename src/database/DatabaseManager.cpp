//
// Created by Oliver Field on 27/10/2025.
//

#include "DatabaseManager.h"

#include <list>

#include "DatabaseHelper.h"
#include <SQLiteCpp/SQLiteCpp.h>

DatabaseManager::DatabaseManager(std::string dbPath) {
    database = new SQLite::Database(dbPath);
    if (!tableExists()) {
        createWeatherTable();
    }
}


bool DatabaseManager::tableExists() {
    try {
        SQLite::Statement query (*database, "SELECT name FROM sqlite_master WHERE type = 'table' and name = 'weather';");

        return query.executeStep() && !query.getColumn(0).isNull();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;

        return false;
    }
}

void DatabaseManager::createWeatherTable() {
    std::string sql = "CREATE TABLE weather ("
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

    database->exec(sql);
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
    SQLite::Statement query (*database, sql);

    std::list<WeatherDataEntity> conditions;

    while (query.executeStep()) {
        conditions.push_back(WeatherDataEntity::fromDB(query));
    }

    return conditions;
}

WeatherDataEntity DatabaseManager::getCurrentConditions() {
    return getRecentConditions(1).front();
}



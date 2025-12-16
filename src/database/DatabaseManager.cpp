//
// Created by Oliver Field on 27/10/2025.
//

#include "DatabaseManager.h"

#include <list>

#include "DatabaseHelper.h"
#include <SQLiteCpp/SQLiteCpp.h>

DatabaseManager::DatabaseManager(std::string dbPath) {
    database = new SQLite::Database(dbPath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
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
            "AirTemp REAL,"
            "FeelsLike REAL,"
            "WindAvg REAL,"
            "WindGust REAL,"
            "WindDir INTEGER,"
            "WindLull REAL,"
            "StationPressure REAL,"
            "Uv REAL,"
            "Brightness INTEGER,"
            "Precip REAL,"
            "PrecipAccumulation REAL,"
            "LocalDayPrecipAccumulation REAL"
        ");";

    database->exec(sql);
}


std::list<WeatherDataEntity> DatabaseManager::getRecentConditions(int count = 0) {
    std::string sql = "SELECT"
            " Timestamp,"
            "AirTemp,"
            "FeelsLike,"
            "WindAvg,"
            "WindGust,"
            "WindDir,"
            "WindLull,"
            "StationPressure,"
            "Uv,"
            "Brightness,"
            "Precip,"
            "PrecipAccumulation,"
            "LocalDayPrecipAccumulation"
            " FROM weather"
            " ORDER BY Timestamp DESC";

    if (count > 0) {
        sql = sql + " LIMIT " + std::to_string(count);
    }

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

void DatabaseManager::insertConditions(WeatherDataEntity conditions) {
    SQLite::Transaction transaction(*database);
    SQLite::Statement statement (*database, "INSERT INTO weather (Timestamp, AirTemp, FeelsLike, WindAvg, WindGust, WindDir, WindLull, StationPressure, Uv, Brightness, Precip, PrecipAccumulation, LocalDayPrecipAccumulation) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)");
    statement.bind(1, conditions.timestamp);
    statement.bind(2, conditions.air_temp);
    statement.bind(3, conditions.feels_like);
    statement.bind(4, conditions.wind_avg);
    statement.bind(5, conditions.wind_gust);
    statement.bind(6, conditions.wind_dir);
    statement.bind(7, conditions.wind_lull);
    statement.bind(8, conditions.station_pressure);
    statement.bind(9, conditions.uv);
    statement.bind(10, conditions.brightness);
    statement.bind(11, conditions.precip);
    statement.bind(12, conditions.precip_accumulation);
    statement.bind(13, conditions.local_day_precip_accumulation);

    statement.exec();
    transaction.commit();
}



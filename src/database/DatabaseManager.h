//
// Created by Oliver Field on 27/10/2025.
//

#ifndef BACKEND_DATABASEMANAGER_H
#define BACKEND_DATABASEMANAGER_H
#include <list>

#include "../entities/WeatherDataEntity.h"
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

class DatabaseManager {
public:
    explicit DatabaseManager(std::string dbPath);

    WeatherDataEntity getCurrentConditions();

    std::list<WeatherDataEntity>  getRecentConditions(int count);

    std::string getCurrentStringValue(std::string column);


private:
    sqlite3 *db;
    SQLite::Database *database;

    bool tableExists();
    void createWeatherTable();

};


#endif //BACKEND_DATABASEMANAGER_H
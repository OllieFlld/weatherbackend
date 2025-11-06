//
// Created by Oliver Field on 27/10/2025.
//

#ifndef BACKEND_DATABASEMANAGER_H
#define BACKEND_DATABASEMANAGER_H
#include <list>

#include "../entities/WeatherDataEntity.h"
#include <sqlite3.h>

class DatabaseManager {
public:
    explicit DatabaseManager(std::string dbPath);
    ~DatabaseManager();

    WeatherDataEntity getCurrentConditions();

    std::list<WeatherDataEntity>  getRecentConditions(int count);
private:
    sqlite3 *db;

    bool tablesExist();
    void createWeatherTable();

};


#endif //BACKEND_DATABASEMANAGER_H
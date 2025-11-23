//
// Created by Oliver Field on 23/11/2025.
//

#ifndef BACKEND_DATABASEMODULE_H
#define BACKEND_DATABASEMODULE_H
#include "BaseModule.h"
#include "../database/DatabaseManager.h"

namespace Modules {
    class Weather : public BaseModule {
    public:
        Weather(DatabaseManager &database);
        std::string getCurrentTemp();

        DatabaseManager *database;
    };
}

#endif //BACKEND_DATABASEMODULE_H

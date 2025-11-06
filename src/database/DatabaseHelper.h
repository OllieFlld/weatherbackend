//
// Created by Oliver Field on 28/10/2025.
//

#ifndef BACKEND_DATABASEHELPER_H
#define BACKEND_DATABASEHELPER_H
#include <unordered_map>


struct  DatabaseHelper {
    public:
    static std::unordered_map<char, char> formatQueryToMap;
};


#endif //BACKEND_DATABASEHELPER_H
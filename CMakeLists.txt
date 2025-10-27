cmake_minimum_required(VERSION 4.0)
project(backend)


set(CMAKE_CXX_STANDARD 20)

add_executable(backend src/main.cpp
        src/entities/WeatherDataEntity.cpp
        src/entities/WeatherDataEntity.h
        src/database/DatabaseManager.cpp
        src/database/DatabaseManager.h
)

find_package(Crow)
target_link_libraries(backend PUBLIC Crow::Crow)

find_package(SQLite3)
target_link_libraries(backend PUBLIC SQLite3)
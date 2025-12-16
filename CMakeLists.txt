cmake_minimum_required(VERSION 4.0)
project(backend)


set(CMAKE_CXX_STANDARD 20)

add_executable(backend src/main.cpp
        src/entities/WeatherDataEntity.cpp
        src/entities/WeatherDataEntity.h
        src/database/DatabaseManager.cpp
        src/database/DatabaseManager.h
        src/database/DatabaseHelper.cpp
        src/database/DatabaseHelper.h
        src/image/Writer.cpp
        src/image/Writer.h
        src/image/Scene.cpp
        src/image/Scene.h
        src/image/Elements/Base.cpp
        src/image/Elements/Base.h
        src/modules/DateTime.cpp
        src/modules/DateTime.h
        src/modules/BaseModule.cpp
        src/modules/BaseModule.h
        src/image/Elements/FunctionCall.cpp
        src/image/Elements/FunctionCall.h
        src/modules/Weather.cpp
        src/modules/Weather.h
        src/datasources/Tempest.cpp
        src/datasources/Tempest.h
)

find_package(Crow)
target_link_libraries(backend PUBLIC Crow::Crow)

find_package(SQLite3)
target_link_libraries(backend PUBLIC SQLite3)

find_package(SQLiteCpp)
target_link_libraries(backend PUBLIC SQLiteCpp)

find_package(PNG REQUIRED)
target_link_libraries (backend PUBLIC ${PNG_LIBRARY})
target_compile_definitions(backend PRIVATE cimg_use_png=1)
target_compile_definitions(backend PRIVATE cimg_display=0)

find_package(cpr REQUIRED)
target_link_libraries(backend PRIVATE cpr::cpr)
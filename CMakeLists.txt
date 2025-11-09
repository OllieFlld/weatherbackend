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
        src/image/Elements/SceneElement.cpp
        src/image/Elements/SceneElement.h
        src/image/Elements/TextElement.cpp
        src/image/Elements/TextElement.h
)

find_package(Crow)
target_link_libraries(backend PUBLIC Crow::Crow)

find_package(SQLite3)
target_link_libraries(backend PUBLIC SQLite3)

find_package(PNG REQUIRED)
target_link_libraries (backend PUBLIC ${PNG_LIBRARY})
target_compile_definitions(backend PRIVATE cimg_use_png=1)
target_compile_definitions(backend PRIVATE cimg_display=0)

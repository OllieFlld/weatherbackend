#include "crow.h"
#include "database/DatabaseManager.h"
#include "Cimg.h"
#include "image/Scene.h"
#include "image/Writer.h"

int main() {
    crow::SimpleApp app;

    DatabaseManager manager = DatabaseManager("weather.sqlite3");

    Scene scene = Scene::fromFile("test.json");



    CROW_ROUTE(app, "/refresh")
            .methods(crow::HTTPMethod::Get)([&manager](const crow::request &req, crow::response &res) {
                WeatherDataEntity conditions = manager.getCurrentConditions();
                Scene scene = Scene::fromFile("test.json");

                std::string path = Writer::write("text.png", scene.draw());
                res.set_static_file_info_unsafe(path);
                res.end();
            });

    app.port(18080).multithreaded().run();
    return 0;
}

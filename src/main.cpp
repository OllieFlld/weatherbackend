#include "crow.h"
#include "database/DatabaseManager.h"
#include "Cimg.h"
#include "image/Scene.h"
#include "image/Writer.h"
#include "modules/DateTime.h"
#include "modules/Weather.h"

int main() {
    crow::SimpleApp app;

    DatabaseManager manager = DatabaseManager("weather.sqlite3");


    std::map<std::string, std::map<std::string, std::function<std::string()>>> allFunctions;

    allFunctions["DateTime"] = Modules::DateTime().functions;
    allFunctions["Weather"] = Modules::Weather(manager).functions;

    CROW_ROUTE(app, "/refresh")
            .methods(crow::HTTPMethod::Get)([allFunctions](const crow::request &req, crow::response &res) {
                Scenes::Scene scene = Scenes::Scene::fromFile("test.json", allFunctions);

                std::string path = Writer::write("text.png", scene.draw());
                res.set_static_file_info_unsafe(path);
                res.end();
            });

    app.port(18080).multithreaded().run();
    return 0;
}

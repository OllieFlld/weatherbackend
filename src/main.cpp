#include "crow.h"
#include "database/DatabaseManager.h"
#include "Cimg.h"
#include "image/Scene.h"
#include "image/Writer.h"
#include "modules/DateTime.h"
#include "modules/Weather.h"
#include "cpr/cpr.h"
#include "datasources/Tempest.h"


int main() {
    crow::SimpleApp app;

    DatabaseManager manager = DatabaseManager("weather.sqlite3");

    DataSources::Tempest tempest(reinterpret_cast<intptr_t>(std::getenv("TEMPEST_STATION")),
                                 std::getenv("TEMPEST_TOKEN"));

    std::map<std::string, std::map<std::string, std::function<std::string()> > > allFunctions;

    allFunctions["DateTime"] = Modules::DateTime().functions;
    allFunctions["Weather"] = Modules::Weather(manager).functions;
    CROW_ROUTE(app, "/refresh")
            .methods(crow::HTTPMethod::Get)([allFunctions](const crow::request &req, crow::response &res) {
                Scenes::Scene scene = Scenes::Scene::fromFile("test.json", allFunctions);

                std::string path = Writer::write("text.png", scene.draw());
                res.set_static_file_info_unsafe(path);
                res.end();
            });

    CROW_ROUTE(app, "/tempest/refresh")
            .methods(crow::HTTPMethod::POST)([&tempest, &manager](const crow::request &req, crow::response &res) {
                WeatherDataEntity conditions = tempest.getMostRecentConditions();
                manager.insertConditions(conditions);
            });

    app.port(18080).multithreaded().run();
    return 0;
}

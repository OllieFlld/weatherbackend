#include "crow.h"
#include "database/DatabaseManager.h"

int main() {
    crow::SimpleApp app;

    DatabaseManager manager = DatabaseManager("weather.sqlite3");

    CROW_ROUTE(app, "/weather/recent")
            .methods(crow::HTTPMethod::Get)([&manager](const crow::request &req) {
                auto conditions = manager.getCurrentConditions();

                return crow::json::wvalue(&conditions);
            });


    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
    return 0;
}

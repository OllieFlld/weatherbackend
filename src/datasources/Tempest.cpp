//
// Created by Oliver Field on 10/12/2025.
//

#include "Tempest.h"

#include <cpr/api.h>
#include <cpr/cprtypes.h>
#include <cpr/parameters.h>

using namespace DataSources;

Tempest::Tempest(int station, std::string token) {
    this->station = station;
    this->token = token;
}

Tempest::Tempest(int station, std::string token, std::string url) {
    this->station = station;
    this->token = token;
    this->url = url;
}


WeatherDataEntity Tempest::getMostRecentConditions() {
    cpr::Response r = cpr::Get(
        cpr::Url{this->url + std::to_string(this->station)},
        cpr::Parameters{{"token", token}}
    );

    crow::json::rvalue json = crow::json::load(r.text);

    if (!json.has("status") || !json["status"].has("status_message") || json["status"]["status_message"] != "SUCCESS") {
        throw new std::runtime_error("Invalid status");
    }

    return WeatherDataEntity::fromJSON(json);
}

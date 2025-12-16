//
// Created by Oliver Field on 22/11/2025.
//

#ifndef BACKEND_FUNCTIONCALLELEMENT_H
#define BACKEND_FUNCTIONCALLELEMENT_H
#include <map>

#include "Base.h"

namespace Scenes::Elements {
    class FunctionCall : public Base {
    public:
        FunctionCall(int x, int y, int width, int height, int fontSize);
        static FunctionCall fromJson(const crow::json::rvalue &, std::map<std::string, std::map<std::string, std::function<std::string()>>> allFunctions);
        std::string callFunction();
    private:
        std::function<std::string()> function;
    };
}


#endif //BACKEND_FUNCTIONCALLELEMENT_H
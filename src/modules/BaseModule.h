//
// Created by Oliver Field on 22/11/2025.
//

#ifndef BACKEND_BASEMODULE_H
#define BACKEND_BASEMODULE_H
#include <list>
#include <map>

namespace Modules {
    class BaseModule {
    public:
        std::map<std::string, std::function<std::string()>> functions;
    };
}



#endif //BACKEND_BASEMODULE_H

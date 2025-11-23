//
// Created by Oliver Field on 22/11/2025.
//

#ifndef BACKEND_DATETIMEMODULE_H
#define BACKEND_DATETIMEMODULE_H
#include <string>

#include "BaseModule.h"
namespace Modules {
    class DateTime: public BaseModule {
    public:
        std::string getCurrentDate();
        DateTime();
    };
}


#endif //BACKEND_DATETIMEMODULE_H
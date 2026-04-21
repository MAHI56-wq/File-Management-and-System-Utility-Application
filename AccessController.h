#pragma once
#include "Structs.h"
#include <string>

class AccessController {
public:
    bool can(const User& u, const std::string& action);
};
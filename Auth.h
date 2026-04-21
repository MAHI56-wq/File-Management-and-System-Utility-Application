#pragma once
#include "Structs.h"
#include <vector>

class Auth {
private:
    std::vector<User> users;

public:
    void init();
    User login(const std::string& u, const std::string& p);
};
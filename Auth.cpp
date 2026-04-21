#include "Auth.h"

void Auth::init() {

    users.push_back({"admin", "1234", UserRole::ADMIN});
    users.push_back({"mahi", "1111", UserRole::EDITOR});
    users.push_back({"guest", "0000", UserRole::VIEWER});
}

User Auth::login(const std::string& u, const std::string& p) {

    for (auto &x : users) {
        if (x.username == u && x.password == p)
            return x;
    }

    return {"", "", UserRole::DENIED};
}
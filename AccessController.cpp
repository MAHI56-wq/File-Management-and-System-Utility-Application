#include "AccessController.h"


bool AccessController::can(const User& u, const std::string& action) {

    
    if (u.role == UserRole::ADMIN)
        return true;

    
    if (u.role == UserRole::EDITOR) {

        if (action == "delete")
            return false;

        return true;
    }

    
    if (u.role == UserRole::VIEWER) {

        if (action == "read" || action == "list")
            return true;

        return false;
    }

    return false;
}
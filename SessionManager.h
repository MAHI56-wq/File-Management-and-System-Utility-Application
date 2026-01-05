#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <string>
#include <chrono>
#include <iostream>

class SessionManager {
private:
    std::string currentUser;
    std::chrono::system_clock::time_point loginTime;
    bool active;

public:
    SessionManager();

    bool startSession(const std::string& username);
    void endSession();
    void showSessionInfo() const;
    bool isActive() const;
};

#endif 

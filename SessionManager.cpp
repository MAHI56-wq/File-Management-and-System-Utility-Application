#include "SessionManager.h"

SessionManager::SessionManager() : active(false) {}

bool SessionManager::startSession(const std::string& username) {
    if (active) {
        std::cout << "A session is already active for user: " << currentUser << "\n";
        return false;
    }
    currentUser = username;
    loginTime = std::chrono::system_clock::now();
    active = true;
    std::cout << "Session started for " << currentUser << " ✅\n";
    return true;
}

void SessionManager::endSession() {
    if (!active) {
        std::cout << "No active session found!\n";
        return;
    }
    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = endTime - loginTime;
    std::cout << "Session ended for " << currentUser 
              << " ⏱ Duration: " << duration.count() << " seconds.\n";
    active = false;
    currentUser.clear();
}

void SessionManager::showSessionInfo() const {
    if (!active) {
        std::cout << "No active session.\n";
        return;
    }
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = now - loginTime;
    std::cout << "User: " << currentUser << "\n"
              << "Session active for: " << duration.count() << " seconds.\n";
}

bool SessionManager::isActive() const {
    return active;
}

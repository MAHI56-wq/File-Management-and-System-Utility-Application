#include "NotificationManager.h"
#include <iostream>

void NotificationManager::addNotification(const std::string& message) {
    notifications.push_back(message);
}

void NotificationManager::showNotifications() const {
    std::cout << "\n=== Notifications ===\n";

    if (notifications.empty()) {
        std::cout << "No notifications available.\n";
        return;
    }

    for (size_t i = 0; i < notifications.size(); i++) {
        std::cout << i + 1 << ". " << notifications[i] << "\n";
    }
}

void NotificationManager::clearNotifications() {
    notifications.clear();
    std::cout << "All notifications cleared.\n";
}

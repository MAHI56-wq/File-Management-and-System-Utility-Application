#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <string>
#include <vector>

class NotificationManager {
private:
    std::vector<std::string> notifications;

public:
    void addNotification(const std::string& message);
    void showNotifications() const;
    void clearNotifications();
};

#endif 

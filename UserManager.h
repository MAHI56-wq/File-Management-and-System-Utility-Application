#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>

class UserManager {
private:
    std::unordered_map<std::string, std::string> users; // username -> password mapping
    std::string dataFile; // ইউজার ডেটা স্টোর করার ফাইল

    void loadUsers(); // ফাইল থেকে ইউজার লোড
    void saveUsers(); // ফাইল এ ইউজার সেভ

public:
    UserManager(const std::string& fileName); // Constructor
    bool registerUser(const std::string& username, const std::string& password); // রেজিস্টার
    bool loginUser(const std::string& username, const std::string& password); // লগইন
};

#endif

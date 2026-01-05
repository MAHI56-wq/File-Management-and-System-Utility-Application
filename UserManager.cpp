#include "UserManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
UserManager::UserManager(const std::string& fileName) {
    dataFile = fileName;
    loadUsers();
}

// ফাইল থেকে ইউজার লোড
void UserManager::loadUsers() {
    std::ifstream inFile(dataFile);
    if(!inFile) return;

    std::string line;
    while(std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string username, password;
        if(std::getline(iss, username, ',') && std::getline(iss, password)) {
            users[username] = password;
        }
    }
    inFile.close();
}

// ফাইল এ ইউজার সেভ
void UserManager::saveUsers() {
    std::ofstream outFile(dataFile);
    for(const auto& pair : users) {
        outFile << pair.first << "," << pair.second << "\n";
    }
    outFile.close();
}

// রেজিস্টার ইউজার
bool UserManager::registerUser(const std::string& username, const std::string& password) {
    if(users.find(username) != users.end()) {
        std::cout << "Username already exists!\n";
        return false;
    }
    users[username] = password;
    saveUsers();
    std::cout << "User registered successfully!\n";
    return true;
}

// লগইন ইউজার
bool UserManager::loginUser(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if(it != users.end() && it->second == password) {
        std::cout << "Login successful! Welcome " << username << "\n";
        return true;
    }
    std::cout << "Invalid username or password!\n";
    return false;
}

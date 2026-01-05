#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>

class UserManager {
private:
    std::unordered_map<std::string, std::string> users; 
    std::string dataFile; 

    void loadUsers(); 
    void saveUsers(); 

public:
    UserManager(const std::string& fileName); 
    bool registerUser(const std::string& username, const std::string& password); 
    bool loginUser(const std::string& username, const std::string& password); 
};

#endif


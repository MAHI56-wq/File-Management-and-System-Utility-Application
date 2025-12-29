#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <ctime>
#include <cstdint>


struct FileInfo {
    std::string name;
    std::string path;
    uintmax_t size = 0;
    std::time_t lastModified = 0;
    bool isDirectory = false;
};

struct FileProperties {
    std::string path;
    bool readable = false;
    bool writable = false;
    bool executable = false;
    uintmax_t size = 0;
    std::time_t modified = 0;
     std::string permissions; 
};


struct Action {
    std::string type;
    std::string targetPath;
    std::string oldValue;
    std::string newValue;
    std::time_t timestamp = 0;
};


enum class UserRole { ADMIN = 0, EDITOR = 1, VIEWER = 2 };


struct User {
    std::string username;
    std::string password; 
    UserRole role = UserRole::VIEWER;
};

#endif 

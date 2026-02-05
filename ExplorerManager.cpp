#include "ExplorerManager.h"
#include <iostream>
#include <unistd.h>   
#include <limits.h>   

ExplorerManager::ExplorerManager() {
    char buff[PATH_MAX];
    if(getcwd(buff, PATH_MAX) != nullptr) {
        currentPath = std::string(buff);
    } else {
        currentPath = ".";
    }
}

std::string ExplorerManager::getCurrentDirectory() const {
    return currentPath;
}

void ExplorerManager::changeDirectory(const std::string& path) {
    if(chdir(path.c_str()) == 0) {
        char buff[PATH_MAX];
        if(getcwd(buff, PATH_MAX) != nullptr)
            currentPath = std::string(buff);
        std::cout << "Directory changed to: " << currentPath << "\n";
    } else {
        std::cerr << "❌ Failed to change directory: " << path << "\n";
    }
}

void ExplorerManager::showCurrentPath() const {
    std::cout << "Current Directory: " << currentPath << "\n";
}

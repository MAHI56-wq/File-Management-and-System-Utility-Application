#pragma once
#include <string>

class ExplorerManager {
private:
    std::string currentPath;

public:
    ExplorerManager();

    
    std::string getCurrentDirectory() const;
    void changeDirectory(const std::string& path);
    void showCurrentPath() const;
};

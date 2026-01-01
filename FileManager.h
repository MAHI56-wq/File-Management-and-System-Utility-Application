#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Structs.h"

class FileManager {
private:
    std::string currentDirectory;

    void ensureTrailingSlash(std::string& path);

public:
    explicit FileManager(const std::string& path = ".");

    std::string getCurrentDirectory() const;

    bool createFile(const std::string& name);
    bool createFolder(const std::string& name);
    bool deleteFile(const std::string& name);
    bool changeDirectory(const std::string& path);

    std::vector<FileInfo> listFiles() const;
};

#endif 

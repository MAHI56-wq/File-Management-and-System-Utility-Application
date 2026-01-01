#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <string>
#include <vector>
#include <ctime>
#include "Structs.h"


class FileUtility {
public:
    static FileProperties getFileProperties(const std::string& filePath);
    static std::vector<FileInfo> listFiles(const std::string& directory);
    static void sortByName(std::vector<FileInfo>& files, bool ascending = true);
    static void sortByDate(std::vector<FileInfo>& files, bool ascending = true);
    static std::vector<FileInfo> searchFile(const std::string& directory, const std::string& keyword);
};

#endif

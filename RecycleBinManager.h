#ifndef RECYCLEBINMANAGER_H
#define RECYCLEBINMANAGER_H

#include <string>
#include <vector>

class RecycleBinManager {
private:
    std::vector<std::string> deletedFiles;
public:
    void moveToRecycleBin(const std::string& fileName);
    void listRecycleBin() const;
};

#endif 
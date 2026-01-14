#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <string>
#include <vector>

struct Version {
    std::string fileName;
    int versionNumber;
    std::string timestamp;
};

class VersionManager {
private:
    std::string versionFolder;
    std::vector<Version> versions;

public:
    VersionManager(const std::string& folder);
    void saveVersion(const std::string& fileName);
    void listVersions(const std::string& fileName) const;
    void restoreVersion(const std::string& fileName, int versionNumber);
};

#endif 

#ifndef VERSIONMANAGER_H
#define VERSIONMANAGER_H

#include <string>
#include <vector>

struct Version {
    std::string file;
    int version;
    std::string backupPath;
};

class VersionManager {
public:
    void saveVersion(const std::string& file);
    void listVersions(const std::string& file);
    bool restoreVersion(const std::string& file, int v);
};

#endif

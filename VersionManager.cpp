#include "VersionManager.h"
#include <iostream>
#include <ctime>

VersionManager::VersionManager(const std::string& folder) : versionFolder(folder) {
    versions.clear();
}

void VersionManager::saveVersion(const std::string& fileName) {
    Version v;
    v.fileName = fileName;
    v.versionNumber = 1; 
    std::time_t t = std::time(nullptr);
    v.timestamp = std::asctime(std::localtime(&t));
    versions.push_back(v);

    std::cout << "Saved version " << v.versionNumber << " for file: " << fileName
              << " at " << v.timestamp;
}

void VersionManager::listVersions(const std::string& fileName) const {
    std::cout << "Versions for " << fileName << ":\n";
    for (const auto& v : versions) {
        if (v.fileName == fileName) {
            std::cout << "Version " << v.versionNumber << " - " << v.timestamp;
        }
    }
}

void VersionManager::restoreVersion(const std::string& fileName, int versionNumber) {
    for (const auto& v : versions) {
        if (v.fileName == fileName && v.versionNumber == versionNumber) {
            std::cout << "Restored version " << versionNumber << " of file " << fileName << "\n";
            return;
        }
    }
    std::cout << "Version not found for file: " << fileName << "\n";
}

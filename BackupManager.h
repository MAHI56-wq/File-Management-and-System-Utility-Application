#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H

#include <string>
#include <vector>

class BackupManager {
private:
    std::string backupFolder;

    // Helper: create folder if not exists
    void ensureFolderExists();

public:
    explicit BackupManager(const std::string& folder = "BackupFolder");

    bool backupFile(const std::string& filePath);
    bool restoreFile(const std::string& backupFileName);
    std::vector<std::string> listBackups() const;
};

#endif // BACKUPMANAGER_H


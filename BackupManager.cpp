#include "BackupManager.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>  // mkdir
#include <dirent.h>    // opendir, readdir
#include <cstring>     // strerror

#ifdef _WIN32
#include <direct.h>
#define mkdir(x,y) _mkdir(x)
#endif

BackupManager::BackupManager(const std::string& folder) : backupFolder(folder) {
    ensureFolderExists();
}

void BackupManager::ensureFolderExists() {
    struct stat info;
    if(stat(backupFolder.c_str(), &info) != 0) {
        if(mkdir(backupFolder.c_str(), 0777) != 0) {
            std::cout << "Failed to create backup folder: " << strerror(errno) << "\n";
        }
    }
}

bool BackupManager::backupFile(const std::string& filePath) {
    std::ifstream src(filePath, std::ios::binary);
    if(!src) {
        std::cout << "File not found: " << filePath << "\n";
        return false;
    }

    std::string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
    std::string destPath = backupFolder + "/" + fileName;

    std::ofstream dest(destPath, std::ios::binary);
    if(!dest) {
        std::cout << "Cannot create backup: " << destPath << "\n";
        return false;
    }

    dest << src.rdbuf();

    src.close();
    dest.close();

    std::cout << "Backup created: " << destPath << "\n";
    return true;
}

bool BackupManager::restoreFile(const std::string& backupFileName) {
    std::string srcPath = backupFolder + "/" + backupFileName;
    std::ifstream src(srcPath, std::ios::binary);
    if(!src) {
        std::cout << "Backup not found: " << backupFileName << "\n";
        return false;
    }

    std::ofstream dest(backupFileName, std::ios::binary);
    if(!dest) {
        std::cout << "Cannot restore file: " << backupFileName << "\n";
        return false;
    }

    dest << src.rdbuf();

    src.close();
    dest.close();

    std::cout << "File restored: " << backupFileName << "\n";
    return true;
}

std::vector<std::string> BackupManager::listBackups() const {
    std::vector<std::string> files;
    DIR* dir = opendir(backupFolder.c_str());
    if(!dir) return files;

    struct dirent* entry;
    while((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if(name != "." && name != "..") {
            files.push_back(name);
        }
    }

    closedir(dir);
    return files;
}

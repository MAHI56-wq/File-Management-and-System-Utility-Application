#include "VersionManager.h"
#include <fstream>
#include <iostream>
#include <direct.h>   


static bool copyFile(const std::string& src, const std::string& dest) {

    std::ifstream in(src, std::ios::binary);
    std::ofstream out(dest, std::ios::binary);

    if (!in || !out) return false;

    out << in.rdbuf();
    return true;
}


static std::vector<Version> versions;


std::string getFileName(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    if (pos == std::string::npos)
        return path;
    return path.substr(pos + 1);
}


void ensureBackupFolder() {
    _mkdir("backup"); 
}


void VersionManager::saveVersion(const std::string& file) {

    std::ifstream test(file);
    if (!test) return;

    ensureBackupFolder();

    std::string name = getFileName(file);

    int v = 1;
    for (auto &x : versions)
        if (x.file == file) v++;

    std::string backup = "backup/" + name + "_v" + std::to_string(v);

    if (!copyFile(file, backup)) {
        std::cout << "❌ Backup failed\n";
        return;
    }

    versions.push_back({file, v, backup});

    std::cout << "✔ Backup saved: " << backup << "\n";
}


void VersionManager::listVersions(const std::string& file) {

    std::cout << "\n===== BACKUPS =====\n";

    bool found = false;

    for (auto &v : versions) {
        if (v.file == file) {
            std::cout << "V" << v.version
                      << " -> " << v.backupPath << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << "No backups found.\n";
}


bool VersionManager::restoreVersion(const std::string& file, int v) {

    for (auto &x : versions) {

        if (x.file == file && x.version == v) {

            std::ifstream in(x.backupPath, std::ios::binary);
            std::ofstream out(file, std::ios::binary);

            if (!in || !out) {
                std::cout << "❌ Restore failed\n";
                return false;
            }

            out << in.rdbuf();

            std::cout << "✔ Restored version V" << v << "\n";
            return true;
        }
    }

    std::cout << "❌ Version not found\n";
    return false;
}


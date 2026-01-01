#include "FileUtility.h"
#include "Structs.h"

#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cerrno>

#ifdef _WIN32
#include <direct.h>
#define stat _stat
#endif


FileProperties FileUtility::getFileProperties(const std::string& filePath) {
    FileProperties prop{};
    struct stat st{};

    if (stat(filePath.c_str(), &st) != 0) {
        std::cerr << "Cannot access file: " << filePath
                  << " (" << strerror(errno) << ")\n";
        return prop;
    }

    
    prop.path = filePath;
    prop.size = static_cast<uintmax_t>(st.st_size);
    prop.modified = st.st_mtime;

    prop.permissions.clear();
    prop.permissions += (st.st_mode & S_IRUSR) ? "r" : "-";
    prop.permissions += (st.st_mode & S_IWUSR) ? "w" : "-";
    prop.permissions += (st.st_mode & S_IXUSR) ? "x" : "-";

    return prop;
}


std::vector<FileInfo> FileUtility::listFiles(const std::string& directory) {
    std::vector<FileInfo> files;

    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        std::cerr << "Cannot open directory: " << directory << "\n";
        return files;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        FileInfo fi{};
        fi.name = name;

        std::string fullPath = directory + "/" + name;
        struct stat st{};
        if (stat(fullPath.c_str(), &st) == 0) {
            fi.isDirectory = S_ISDIR(st.st_mode);
            fi.lastModified = st.st_mtime;   
            fi.size = st.st_size;
        } else {
            fi.isDirectory = false;
            fi.lastModified = 0;
            fi.size = 0;
        }

        files.push_back(fi);
    }

    closedir(dir);
    return files;
}


void FileUtility::sortByName(std::vector<FileInfo>& files, bool ascending) {
    std::sort(files.begin(), files.end(),
        [ascending](const FileInfo& a, const FileInfo& b) {
            return ascending ? (a.name < b.name)
                             : (a.name > b.name);
        });
}


void FileUtility::sortByDate(std::vector<FileInfo>& files, bool ascending) {
    std::sort(files.begin(), files.end(),
        [ascending](const FileInfo& a, const FileInfo& b) {
            return ascending
                ? (a.lastModified < b.lastModified)
                : (a.lastModified > b.lastModified);
        });
}


std::vector<FileInfo> FileUtility::searchFile(
        const std::string& directory,
        const std::string& keyword) {

    std::vector<FileInfo> results;

    DIR* dir = opendir(directory.c_str());
    if (!dir) return results;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        if (name.find(keyword) != std::string::npos) {
            FileInfo fi{};
            fi.name = name;

            std::string fullPath = directory + "/" + name;
            struct stat st{};
            if (stat(fullPath.c_str(), &st) == 0) {
                fi.isDirectory = S_ISDIR(st.st_mode);
                fi.lastModified = st.st_mtime;
                fi.size = st.st_size;
            } else {
                fi.isDirectory = false;
                fi.lastModified = 0;
                fi.size = 0;
            }

            results.push_back(fi);
        }
    }

    closedir(dir);
    return results;
}

#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>  
#include <dirent.h>    
#include <unistd.h>    
#include <cstring>     

#ifdef _WIN32
#include <direct.h>
#define mkdir(x,y) _mkdir(x)
#define chdir _chdir
#define getcwd _getcwd
#endif

FileManager::FileManager(const std::string& path) {
    currentDirectory = path;
    ensureTrailingSlash(currentDirectory);
}

std::string FileManager::getCurrentDirectory() const {
    return currentDirectory;
}

void FileManager::ensureTrailingSlash(std::string& path) {
    if(!path.empty() && path.back() != '/' && path.back() != '\\') {
        path += "/";
    }
}

bool FileManager::createFile(const std::string& name) {
    std::ofstream file(currentDirectory + name);
    if(!file) {
        std::cout << "Cannot create file: " << name << "\n";
        return false;
    }
    file.close();
    return true;
}

bool FileManager::createFolder(const std::string& name) {
    std::string fullPath = currentDirectory + name;
    if(mkdir(fullPath.c_str(), 0777) != 0) {
        std::cout << "Cannot create folder: " << name << " (" << strerror(errno) << ")\n";
        return false;
    }
    return true;
}

bool FileManager::deleteFile(const std::string& name) {
    std::string fullPath = currentDirectory + name;
    if(remove(fullPath.c_str()) != 0) {
        std::cout << "Cannot delete file: " << name << " (" << strerror(errno) << ")\n";
        return false;
    }
    return true;
}

bool FileManager::changeDirectory(const std::string& path) {
    if(chdir(path.c_str()) != 0) {
        std::cout << "Cannot change directory: " << path << " (" << strerror(errno) << ")\n";
        return false;
    }

    char buffer[1024];
    if(getcwd(buffer, sizeof(buffer)) != nullptr) {
        currentDirectory = buffer;
        ensureTrailingSlash(currentDirectory);
        return true;
    } else {
        std::cout << "Cannot get current directory\n";
        return false;
    }
}

std::vector<FileInfo> FileManager::listFiles() const {
    std::vector<FileInfo> files;
    DIR* dir = opendir(currentDirectory.c_str());
    if(!dir) {
        std::cout << "Cannot open directory: " << currentDirectory << "\n";
        return files;
    }

    struct dirent* entry;
    while((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if(name == "." || name == "..") continue;
        FileInfo fi;
        fi.name = name;
#ifdef _WIN32
        fi.isDirectory = (entry->d_type == DT_DIR);
#else
        struct stat st;
        if(stat((currentDirectory + name).c_str(), &st) == 0) {
            fi.isDirectory = S_ISDIR(st.st_mode);
        } else {
            fi.isDirectory = false;
        }
#endif
        files.push_back(fi);
    }

    closedir(dir);
    return files;
}

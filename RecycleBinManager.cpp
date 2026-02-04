#include "RecycleBinManager.h"
#include <iostream>

void RecycleBinManager::moveToRecycleBin(const std::string& fileName) {
    deletedFiles.push_back(fileName);
    std::cout << "Moved '" << fileName << "' to Recycle Bin.\n";
}

void RecycleBinManager::listRecycleBin() const {
    std::cout << "--- Recycle Bin ---\n";
    if(deletedFiles.empty()) {
        std::cout << "Recycle Bin is empty.\n";
    } else {
        for(const auto& f : deletedFiles)
            std::cout << f << "\n";
    }
}
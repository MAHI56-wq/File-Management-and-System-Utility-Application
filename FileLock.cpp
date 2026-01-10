#include "FileLock.h"

bool FileLock::lockFile(const string& fileName) {
    if(lockedFiles.count(fileName)) return false;
    lockedFiles.insert(fileName);
    return true;
}

bool FileLock::unlockFile(const string& fileName) {
    return lockedFiles.erase(fileName) > 0;
}

bool FileLock::isLocked(const string& fileName) const {
    return lockedFiles.count(fileName) > 0;
}

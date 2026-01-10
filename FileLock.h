#ifndef FILELOCK_H
#define FILELOCK_H

#include <string>
#include <unordered_set>

using namespace std;

class FileLock {
private:
    unordered_set<string> lockedFiles;
public:
    bool lockFile(const string& fileName);
    bool unlockFile(const string& fileName);
    bool isLocked(const string& fileName) const;
};

#endif 

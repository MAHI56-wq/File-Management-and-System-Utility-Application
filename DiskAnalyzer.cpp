#include "DiskAnalyzer.h"
#include <iostream>
#include <windows.h>
#include <vector>

static long long totalSize = 0;
static int fileCount = 0;
static int folderCount = 0;
static std::string largestFile;
static long long maxSize = 0;

static long long getFileSize(const std::string& file) {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (!GetFileAttributesExA(file.c_str(), GetFileExInfoStandard, &fad))
        return 0;

    LARGE_INTEGER size;
    size.HighPart = fad.nFileSizeHigh;
    size.LowPart = fad.nFileSizeLow;

    return size.QuadPart;
}

static void traverse(const std::string& path) {
    std::string searchPath = path + "\\*";

    WIN32_FIND_DATAA data;
    HANDLE h = FindFirstFileA(searchPath.c_str(), &data);

    if (h == INVALID_HANDLE_VALUE) return;

    do {
        std::string name = data.cFileName;
        if (name == "." || name == "..") continue;

        std::string full = path + "\\" + name;

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            folderCount++;
            traverse(full);
        } else {
            fileCount++;
            long long sz = getFileSize(full);
            totalSize += sz;
            if (sz > maxSize) {
                maxSize = sz;
                largestFile = full;
            }
        }

    } while (FindNextFileA(h, &data));

    FindClose(h);
}

void DiskAnalyzer::analyze(const std::string& path) {
    totalSize = 0;
    fileCount = 0;
    folderCount = 0;
    largestFile = "";
    maxSize = 0;

    traverse(path);

    std::cout << "\n===== DISK ANALYSIS REPORT =====\n";
    std::cout << "Files     : " << fileCount << "\n";
    std::cout << "Folders   : " << folderCount << "\n";
    std::cout << "Total Size: " << totalSize << " bytes\n";

    if (!largestFile.empty())
        std::cout << "Largest File: " << largestFile
                  << " (" << maxSize << " bytes)\n";
}
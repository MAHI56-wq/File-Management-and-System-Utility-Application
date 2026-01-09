#include "EncryptionManager.h"

EncryptionManager::EncryptionManager(char k) : key(k) {}

bool EncryptionManager::encryptFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream in(inputPath, std::ios::binary);
    if (!in) {
        std::cout << "❌ Cannot open input file: " << inputPath << "\n";
        return false;
    }

    std::ofstream out(outputPath, std::ios::binary);
    if (!out) {
        std::cout << "❌ Cannot create output file: " << outputPath << "\n";
        return false;
    }

    char ch;
    while (in.get(ch)) {
        ch ^= key;          
        out.put(ch);
    }

    std::cout << " File encrypted: " << outputPath << "\n";
    return true;
}

bool EncryptionManager::decryptFile(const std::string& inputPath, const std::string& outputPath) {
    return encryptFile(inputPath, outputPath);
}

#ifndef ENCRYPTIONMANAGER_H
#define ENCRYPTIONMANAGER_H

#include <string>
#include <iostream>
#include <fstream>

class EncryptionManager {
private:
    char key; 
public:
    explicit EncryptionManager(char k = 'K');
    bool encryptFile(const std::string& inputPath, const std::string& outputPath);
    bool decryptFile(const std::string& inputPath, const std::string& outputPath);
};

#endif 

#ifndef CRYPTOMANAGERPRO_H
#define CRYPTOMANAGERPRO_H

#include <string>

using namespace std;

class CryptoManagerPro {
private:
    string key;
public:
    explicit CryptoManagerPro(const string& k = "K");
    bool encryptFile(const string& fileName);
    bool decryptFile(const string& fileName);
};

#endif 

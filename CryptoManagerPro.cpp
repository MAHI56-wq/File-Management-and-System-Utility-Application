#include "CryptoManagerPro.h"
#include <fstream>
#include <iostream>

using namespace std;

CryptoManagerPro::CryptoManagerPro(const string& k) : key(k) {}

bool CryptoManagerPro::encryptFile(const string& fileName) {
    ifstream in(fileName, ios::binary);
    if(!in) return false;

    ofstream out(fileName + ".enc", ios::binary);
    char ch;
    while(in.get(ch)) {
        ch ^= key[0]; 
        out.put(ch);
    }
    in.close();
    out.close();
    return true;
}

bool CryptoManagerPro::decryptFile(const string& fileName) {
    ifstream in(fileName, ios::binary);
    if(!in) return false;

    string outName = fileName;
    if(fileName.size() > 4 && fileName.substr(fileName.size()-4) == ".enc")
        outName = fileName.substr(0, fileName.size()-4);

    ofstream out(outName, ios::binary);
    char ch;
    while(in.get(ch)) {
        ch ^= key[0]; 
        out.put(ch);
    }
    in.close();
    out.close();
    return true;
}

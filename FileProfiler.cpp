#include "FileProfiler.h"
#include <iostream>
#include <fstream>
#include <cctype>

void FileProfiler::analyze(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        std::cout << "❌ Cannot open file\n";
        return;
    }
    char c;
    int letters = 0, digits = 0, spaces = 0, symbols = 0, total = 0;

    while (in.get(c)) {
        total++;
        if (std::isalpha((unsigned char)c)) letters++;
        else if (std::isdigit((unsigned char)c)) digits++;
        else if (std::isspace((unsigned char)c)) spaces++;
        else symbols++;
    }

    std::cout << "\n===== FILE PROFILE =====\n";
    std::cout << "Total chars: " << total << "\n";
    std::cout << "Letters: " << letters << "\n";
    std::cout << "Digits: " << digits << "\n";
    std::cout << "Spaces: " << spaces << "\n";
    std::cout << "Symbols: " << symbols << "\n";

    if (digits > letters)
        std::cout << "⚠ Numeric-heavy file (log/binary-like)\n";
    else if (symbols > letters)
        std::cout << "⚠ Symbol-heavy file (code/config-like)\n";
    else
        std::cout << "✔ Normal text file\n";
}
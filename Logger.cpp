#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

Logger::Logger(const std::string& fname) : fileName(fname) {}

void Logger::log(const std::string& msg, LogCategory cat) {
    ofstream out(fileName, ios::app);
    if(!out) return;

    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    const char* tag = (cat==LINFO ? "INFO" : (cat==LWARN ? "WARN" : "ERROR"));
    out << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S")
        << " [" << tag << "] " << msg << "\n";
    out.close();
}

vector<string> Logger::readLastLines(int n) const {
    vector<string> lines;
    ifstream in(fileName);
    if(!in) return lines;

    string line;
    while(getline(in, line)) lines.push_back(line);
    in.close();

    if((int)lines.size() > n) {
        return vector<string>(lines.end()-n, lines.end());
    }
    return lines;
}

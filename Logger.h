#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum LogCategory { LINFO, LWARN, LERROR };

class Logger {
private:
    std::string fileName;
public:
    explicit Logger(const std::string& fname = "actions.log");
    void log(const std::string& msg, LogCategory cat = LINFO);
    std::vector<std::string> readLastLines(int n = 50) const;
};

#endif 

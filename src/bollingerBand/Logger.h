#include <list>
#include <string>
#pragma once

class Logger {
public:
    Logger();
    ~Logger();    
    void addMessage(std::string message);
    void logMessage();
private:
    std::list<std::string> *messages;
};

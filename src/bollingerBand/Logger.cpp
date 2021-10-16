#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;

Logger::Logger() {
  messages = new std::list<string>();
}

Logger::~Logger() {
  delete messages;
}

//optimise to store these and then print on command when out of the hotpath
void Logger::addMessage(string message) {
    messages->push_back(message);
}

void Logger::logMessage() {
    cout << messages->front() << "\n";
    messages->pop_front();
}

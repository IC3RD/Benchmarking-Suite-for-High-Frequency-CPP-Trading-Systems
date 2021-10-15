#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;

//optimise to store these and then print on command when out of the hotpath
void Logger::log(const string message) {
    cout << message << "\n";
}
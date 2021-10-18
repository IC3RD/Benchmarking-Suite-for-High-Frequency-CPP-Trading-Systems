#include <list>
#include <string>
#include <Order.h>
#pragma once
using namespace std;

class Logger {
public:
    Logger();
    ~Logger();    
    void addMessage(string message);
    void logMessage();
    void addOrder(Order order);
    void printAllOrders();

private:
    list<string> *messages;
    list<Order> *orders;
};

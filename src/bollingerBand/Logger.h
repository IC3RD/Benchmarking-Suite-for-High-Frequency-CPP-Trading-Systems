#include <list>
#include <string>
#include "Order.h"
#include "BitMEXApi.h"

#pragma once

#define BITMEX_KEY "unkdj30VcxpWe9Yeam8t7mxP"
#define BITMEX_SECRET "xx3NBrE_qj_TwbWEki3JYEqp2EgMVfQw59bOCMZupYhKs4UD"

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
    BitMEXApi bitmex = BitMEXApi(BITMEX_KEY, BITMEX_SECRET);
};

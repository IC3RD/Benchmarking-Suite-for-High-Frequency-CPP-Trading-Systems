#include "Order.h"

#include <iostream>
#include <map>

#include "exchange/Exchange.h"

Order::Order(const std::string s, int p, int v, bool isBuy, bool isTest)
    : symbol(s), price(p), volume(v), isBuy(isBuy), isTest(isTest){};

int Order::getVolume() const { return volume; }

int Order::getPrice() constg { return price; }

std::string Order::getSymbol() const { return symbol; }

bool Order::isBuyOrder() const { return isBuy; }

bool Order::isTestOrder() const { return isTest; }

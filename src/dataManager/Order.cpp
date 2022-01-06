#include "Order.h"

#include <iostream>
#include <map>

#include "exchange/Exchange.h"

Order::Order(const std::string s, long long p, int v, bool isBuy)
    : symbol(s), price(p), volume(v), isBuy(isBuy){};

int Order::getVolume() const { return volume; }

long long Order::getPrice() const { return price; }

std::string Order::getSymbol() const { return symbol; }

bool Order::isBuyOrder() const { return isBuy; }

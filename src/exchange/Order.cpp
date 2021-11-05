#include "Order.h"

#include <iostream>
#include <map>

#include "exchange/Exchange.h"

Order::Order(const std::string s, int p, int v, bool isBuy)
    : symbol(s), price(p), volume(v), isBuy(isBuy){};

int Order::getVolume() const { return volume; }

int Order::getPrice() const { return price; }

std::string Order::getSymbol() const { return symbol; }

bool Order::isBuyOrder() const { return isBuy; }

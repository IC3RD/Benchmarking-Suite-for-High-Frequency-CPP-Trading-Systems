
#include "Order.h"
#include <iostream>
#include <map>
using namespace std;

Order::Order(const string s, int buy, int sell, int v, bool isBuy) : symbol(s), price(isBuy ? buy : sell), volume(v), sellPrice(sell), buyPrice(buy), isBuy(isBuy) {};    

int Order::getVolume() const
{
    return volume;
}

int Order::getPrice() const
{
    return price;
}

string Order::getSymbol() const
{
    return symbol;
}

bool Order::isBuy() const
{
    return isBuy;
}




#include "Order.h"
#include <iostream>
#include <map>
using namespace std;

Order::Order(const string s, int p, int v, bool isBuy) 
    : symbol(s), price(p), volume(v), isBuy(isBuy) {};    

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

bool Order::isBuyOrder() const
{
    return isBuy;
}




#include "MarketData.h"
using namespace std;

MarketData::MarketData(const string s, double p, int v) : symbol(s), price(p), volume(v) {};    

int MarketData::getVolume() const
{
    return volume;
}

double MarketData::getPrice() const
{
    return price;
}

string MarketData::getSymbol() const
{
    return symbol;
}
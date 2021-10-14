
#include "MarketData.h"
using namespace std;

MarketData::MarketData(const string s, double p, int v) : symbol(s), price(p), volume(v) {};    

int MarketData::getVolume()
{
    return volume;
}

double MarketData::getPrice()
{
    return price;
}

string MarketData::getSymbol()
{
    return symbol;
}
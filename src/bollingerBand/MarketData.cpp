
#include "MarketData.h"
using namespace std;

MarketData::MarketData(const string s, int buy, int sell, int v) : symbol(s), price(buy + sell / 2), volume(v), sellPrice(sell), buyPrice(buy) {};    

int MarketData::getVolume() const
{
    return volume;
}

int MarketData::getPrice() const
{
    return price;
}

string MarketData::getSymbol() const
{
    return symbol;
}

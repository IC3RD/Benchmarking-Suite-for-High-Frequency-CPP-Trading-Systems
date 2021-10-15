#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class MarketData {
    public:
        MarketData(string, int, int, int);
        int getVolume() const;
        int getPrice() const;
        string getSymbol() const;   

    private:
        const string symbol;
        const int price;
        const int volume;
        const int sellPrice;
        const int buyPrice;     
};

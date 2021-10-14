#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class MarketData {
    public:
        MarketData(string, double, int);
        int getVolume() const;
        double getPrice() const;
        string getSymbol() const;   

    private:
        const string symbol;
        const double price;
        const int volume;     
};
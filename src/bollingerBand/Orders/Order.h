#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class Order {
    public:
        Order(string, int, int, int, bool);
        int getVolume() const;
        int getPrice() const;
        bool isBuy() const;
        string getSymbol() const;   
        bool isBuy() const;

    private:
        const string symbol;
        const int price;
        const int volume;
        const int sellPrice;
        const int buyPrice;  
        const bool isBuy; // If not it is a sell order   
};

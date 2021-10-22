#include <stdio.h>
#include <string>
#pragma once

using namespace std;

class Order {
    public:
        Order(string, int, int, bool);
        int getVolume() const;
        int getPrice() const;
        bool isBuyOrder() const;
        string getSymbol() const;   

    private:
        const string symbol;
        const int price;
        const int volume;
        const bool isBuy; // If not it is a sell order   
};

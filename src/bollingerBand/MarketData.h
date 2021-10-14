#include <stdio.h>
#include <string>

using namespace std;

class MarketData {
    public:
        MarketData(string, double, int);
        int getVolume();
        double getPrice();
        string getSymbol();   

    private:
        const string symbol;
        const double price;
        const int volume;     
};
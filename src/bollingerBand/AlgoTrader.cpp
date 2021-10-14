#include <iostream>
#include <stdio.h>
#ifndef Band
#define Band
#include "BollingerBand.h"
#include "MarketData.h"

using namespace std;

int main()
{
    MarketData data = MarketData("Bitcoin", 3.5, 10);
    cout << "Price is " << data.getPrice();
    cout << "Volume is " << data.getVolume();
    cout << "Symbol is " << data.getSymbol();

    BollingerBand band1 = BollingerBand(10);
    band1.insertNewData(data);
    cout << band1.getCurrMovingAverage() << "\n";
    cout << band1.getCurrStdDeviation() << "\n";
    return 0;

}

#endif
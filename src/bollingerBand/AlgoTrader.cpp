#include <iostream>
#include <stdio.h>
#ifndef Band
#define Band
#include "BollingerBand.h"
#include "MarketData.h"

using namespace std;

int main()
{
    const MarketData& data = MarketData("Bitcoin", 3, 10);
    const MarketData& data1 = MarketData("Bitcoin", 4, 10);
    const MarketData& data2 = MarketData("Bitcoin", 5, 10);

    cout << "Price is " << data.getPrice() << "\n";
    cout << "Volume is " << data.getVolume() << "\n";
    cout << "Symbol is " << data.getSymbol() << "\n";

    BollingerBand band1 = BollingerBand(10);
    band1.insertNewData(data);
    band1.insertNewData(data1);
    band1.insertNewData(data2);

    cout << "Curr moving average is "<< band1.getCurrMovingAverage() << "\n";
    cout << "Curr std dev is "<< band1.getCurrStdDeviation() << "\n";
    return 0;

}

#endif
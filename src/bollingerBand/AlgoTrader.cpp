#include <iostream>
#include <stdio.h>
#ifndef Band
#define Band
#include "BollingerBand.h"
#include "MarketData.h"

using namespace std;

int main()
{
    MarketData *data = new MarketData("Bitcoin", 4, 2, 10);
    BollingerBand *band = data->getStrategy();

    cout << "Price is " << data->getPrice() << "\n";
    cout << "Volume is " << data->getVolume() << "\n";
    cout << "Symbol is " << data->getSymbol() << "\n"; 
    data->newMarketData();

    data->updateBuy(5);
    data->updateSell(3);
    data->newMarketData();
    
    data->updateBuy(6);
    data->updateSell(4);
    data->newMarketData();
    
    cout << "Curr moving average is "<< band->getCurrMovingAverage() << "\n";
    cout << "Curr std dev is "<< band->getCurrStdDeviation() << "\n";
    return 0;

}

#endif

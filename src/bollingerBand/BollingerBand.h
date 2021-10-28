#pragma once
#include <stdio.h>
#include <deque>
#include "MarketData.h"
#include "Logger.h"
using namespace std;

class MarketData;

class BollingerBand {
public:
    double getCurrMovingAverage();
    double getCurrStdDeviation();
    void strategy(MarketData *data);
    BollingerBand(int max);
    ~BollingerBand();
private:
    void process(MarketData const *data);
    void buy(MarketData const *data);
    void sell(MarketData const *data);
    int currElementCount;
    int currentHeldVolume;    
    const int maxElements;
    double currAvg;
    double currStdDev;
    deque<double> *marketPrices;
    Logger *logger;
};

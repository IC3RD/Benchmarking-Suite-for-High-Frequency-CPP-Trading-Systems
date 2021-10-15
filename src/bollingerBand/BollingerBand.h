#include <stdio.h>
#include <deque>
#include "MarketData.h"
#include "Logger.h"
#pragma once
using namespace std;

class BollingerBand {
public:
    double getCurrMovingAverage();
    double getCurrStdDeviation();
    void insertNewData(const MarketData& data);
    BollingerBand(int max);
    ~BollingerBand();
private:
    void process(const MarketData& data);
    void buy(const MarketData& data);
    void sell(const MarketData& data);
    int currElementCount;
    int currentHeldVolume;    
    const int maxElements;
    double currAvg;
    double currStdDev;
    deque<double> *marketPrices;
    Logger *logger;
};

#ifndef Band
#define Band
#include <stdio.h>
#include <deque>
#include "MarketData.h"
using namespace std;

class BollingerBand {
public:
    double getCurrMovingAverage();
    double getCurrStdDeviation();
    void insertNewData(MarketData& data);
    BollingerBand(int max);
    ~BollingerBand();
private:
    void process(MarketData& data);
    void buy(MarketData& data);
    void sell(MarketData& data);
    int currElementCount;
    const int maxElements;
    double currAvg;
    double currStdDev;
    deque<double> *marketPrices;
};

#endif //band
/home/peter/Documents/Year-3/autumn/cpp/BollingerBand.cpp
#include <deque>
#include <math.h>
#ifndef Band
#define Band
#include "BollingerBand.h"
#include "MarketData.h"
#include "Logger.h"
using namespace std;

BollingerBand::BollingerBand(int max) : maxElements(max) {
    currElementCount = 0;
    currAvg = 0;
    currStdDev = 0;
    allocator<double> alloc;
   // initialise memory for the queue all at initialisation
    marketPrices = &deque<double> (sizeof(double) * maxElements, alloc);
}

BollingerBand::~BollingerBand() {
    delete marketPrices;
}

void BollingerBand::insertNewData(MarketData& data) {
    double removed = 0;
    int newElementCount = currElementCount + 1;
    if (currElementCount == maxElements) {
        removed = marketPrices->front();
        marketPrices->pop_front();
        newElementCount = maxElements;
    }
    marketPrices->push_back(data.getPrice());
    // calculate the new average from the old one
    double newAvg = (currAvg * currElementCount - removed + data.getPrice()) / newElementCount;
    double sumSquareMeanDiffs = 0;
    for (auto it = marketPrices->cbegin(); it != marketPrices->cend(); ++it) {
        sumSquareMeanDiffs += (*it) * (*it) - newAvg * newAvg;
    }
    
    currElementCount = newElementCount;
    currAvg = newAvg;
    currStdDev = sqrt(sumSquareMeanDiffs / newElementCount);

    process(data);
}

double BollingerBand::getCurrMovingAverage() {
    return currAvg;
}

double BollingerBand::getCurrStdDeviation() {
    return currStdDev;
}

void BollingerBand::process(MarketData& data) {
    if (data.getPrice() >= currAvg + currStdDev) {
        buy(data);
    }
    if (data.getPrice() <= currAvg - currStdDev) {
        sell(data);
    }
}

void BollingerBand::buy(MarketData& data) {
    Logger::log("buy " + data.getSymbol());
}

void BollingerBand::sell(MarketData& data) {
    Logger::log("sell " + data.getSymbol());
}

#endif
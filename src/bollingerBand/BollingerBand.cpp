#include <deque>
#include <math.h>
#include <iostream>
#include "BollingerBand.h"
#include "MarketData.h"
#include "Logger.h"
using namespace std;

BollingerBand::BollingerBand(int max) : maxElements(max) {
    currElementCount = 0;
    currAvg = 0;
    currStdDev = 0;
    currentHeldVolume = 0;
   // initialise memory for the queue all at initialisation
    marketPrices = new deque<double>(max);
    logger = new Logger();
}

BollingerBand::~BollingerBand() {
    delete marketPrices;
}

void BollingerBand::insertNewData(const MarketData& data) {
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
    auto it = marketPrices->cend();
    --it; //Since cend() points to the element after the back of the queue
    for (int i = 0; i < newElementCount && it != marketPrices->cbegin(); ++i) {
        sumSquareMeanDiffs += (*it) * (*it) - newAvg * newAvg;
        --it;
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

void BollingerBand::process(const MarketData& data) {
    if (currStdDev != 0) {
        if (data.getPrice() <= currAvg - 2 * currStdDev) {
            buy(data);
            ++currentHeldVolume;
        }
        if (data.getPrice() >= currAvg + 2 * currStdDev) {
            sell(data);
            --currentHeldVolume;
        }
    }
}

void BollingerBand::buy(const MarketData& data) {
    logger->addMessage("buy " + data.getSymbol() + "\n");
}

void BollingerBand::sell(const MarketData& data) {
    logger->addMessage("sell " + data.getSymbol() + "\n");
}

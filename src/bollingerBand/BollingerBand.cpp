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
    //delete logger;
}

void BollingerBand::strategy(MarketData *data) {
    double removed = 0;
    int newElementCount = currElementCount + 1;
    if (currElementCount == maxElements) {
        removed = marketPrices->front();
        marketPrices->pop_front();
        newElementCount = maxElements;
    }
    marketPrices->push_back(data->getPrice());
    // calculate the new average from the old one
    double newAvg = (currAvg * currElementCount - removed + data->getPrice()) / newElementCount;
    double sumSquareMeanDiffs = 0;
    auto it = marketPrices->cend();
    --it; //Since cend() points to the element after the back of the queue
    for (int i = 0; i < newElementCount && it != marketPrices->cbegin(); ++i) {
        sumSquareMeanDiffs += (*it) * (*it) - newAvg * newAvg;
        --it;
    }
    currElementCount = newElementCount;
    currAvg = newAvg;
    if (newElementCount <= 1) {
      currStdDev = 0;
    } else {
      currStdDev = sqrt(sumSquareMeanDiffs / (newElementCount - 1));
    } 
    process(data);
}

double BollingerBand::getCurrMovingAverage() {
    return currAvg;
}

double BollingerBand::getCurrStdDeviation() {
    return currStdDev;
}

void BollingerBand::process(MarketData const *data) {
    if (currStdDev != 0) {
        if (data->getBuyPrice() <= currAvg - 2 * currStdDev) {
            buy(data);
            ++currentHeldVolume;
        }
        if (data->getSellPrice() >= currAvg + 2 * currStdDev) {
            sell(data);
            --currentHeldVolume;
        }
    }
}

void BollingerBand::buy(MarketData const *data) {
    cout << "Buy\n";
    logger->addMessage("buy " + data->getSymbol() + "\n");
    logger->addOrder(Order(data->getSymbol(), data->getBuyPrice(), 1, true));
}

void BollingerBand::sell(MarketData const *data) {
    cout << "Sell\n";
    logger->addMessage("sell " + data->getSymbol() + "\n");
    logger->addOrder(Order(data->getSymbol(), data->getSellPrice(), 1, false));
}

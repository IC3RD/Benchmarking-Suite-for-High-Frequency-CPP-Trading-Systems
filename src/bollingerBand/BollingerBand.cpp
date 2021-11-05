#include "BollingerBand.h"

#include <math.h>

#include <deque>
#include <iostream>

#include "../exchange/Exchange.h"
#include "../exchange/MarketData.h"
using namespace std;

BollingerBand::BollingerBand(int max) : maxElements(max) {
  currElementCount = 0;
  currAvg = 0;
  currStdDev = 0;
  // initialise memory for the queue all at initialisation
  marketPrices = new std::deque<double>(max);
}

BollingerBand::~BollingerBand() { delete marketPrices; }

void BollingerBand::runStrategy() {
  int numOfValidMarketData = 0;
  int totalPrices = 0;
  for (std::pair<Exchange::ExchangeName, MarketData&> element : exchangeData) {
    if (element.second.getBuyPrice() != -1 &&
        element.second.getSellPrice() != -1) {
      numOfValidMarketData++;
      totalPrices +=
          (element.second.getBuyPrice() + element.second.getSellPrice()) / 2;
    }
  }
  if (numOfValidMarketData == 0) {
    return;
  }
  totalPrices /= numOfValidMarketData;

  double removed = 0;
  int newElementCount = currElementCount + 1;
  if (currElementCount == maxElements) {
    removed = marketPrices->front();
    marketPrices->pop_front();
    newElementCount = maxElements;
  }
  marketPrices->push_back(totalPrices);
  // calculate the new average from the old one
  double newAvg =
      (currAvg * currElementCount - removed + totalPrices) / newElementCount;
  double sumSquareMeanDiffs = 0;
  auto it = marketPrices->cend();
  --it;  // Since cend() points to the element after the back of the queue
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
  if (currStdDev != 0) {
    for (std::pair<Exchange::ExchangeName, MarketData&> element :
         exchangeData) {
      if (element.second.getBuyPrice() <= currAvg - 2 * currStdDev) {
        buy(element.second);
      }
      if (element.second.getSellPrice() >= currAvg + 2 * currStdDev) {
        sell(element.second);
      }
    }
  }
}

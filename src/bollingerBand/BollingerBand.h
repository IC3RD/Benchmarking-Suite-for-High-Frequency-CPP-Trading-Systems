#include <deque>
#include <stdio.h>
#include "../exchange/MarketData.h"
#include "../ordering-system/OrderExecutor.h"
#include "../exchange/Order.h"
#pragma once
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
  std::deque<double> *marketPrices;
  OrderExecutor *orderExecutor;
};

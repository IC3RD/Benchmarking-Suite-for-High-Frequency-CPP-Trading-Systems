#pragma once
#include <deque>
#include <stdio.h>
#include "../exchange/MarketData.h"
#include "../ordering-system/OrderExecutor.h"
#include "../exchange/Order.h"
#include "../exchange/TradingStrategy.h"

class BollingerBand : TradingStrategy {
public:
  BollingerBand(int max);
  ~BollingerBand();
  void runStrategy(MarketData *data);
private:
  void process(MarketData const *data);
  int currElementCount;
  int currentHeldVolume;
  const int maxElements;
  double currAvg;
  double currStdDev;
  std::deque<double> *marketPrices;
};
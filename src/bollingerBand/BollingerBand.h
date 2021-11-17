#pragma once
#include <stdio.h>

#include <deque>

#include "../exchange/MarketData.h"
#include "../exchange/Order.h"
#include "../exchange/TradingStrategy.h"

class BollingerBand : public TradingStrategy {
 public:
  BollingerBand(int max);
  ~BollingerBand();
  void runStrategy();

 private:
  // void process(MarketData const *data);
  int currElementCount;
  int currentHeldVolume;
  const int maxElements;
  double currAvg;
  double currStdDev;
  std::deque<double> *marketPrices;
};
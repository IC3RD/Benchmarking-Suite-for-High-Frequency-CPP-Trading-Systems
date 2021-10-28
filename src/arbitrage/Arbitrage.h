#pragma once

#include <stdio.h>

#include <deque>

#include "Logger.h"
#include "MarketData.h"

using namespace std;

class Arbitrage {
 public:
  void strategy(MarketData *bitmexData, MarketData *binanceData, MarketData *coinbaseData);
  Arbitrage(int max);
  ~Arbitrage();

 private:
  void process(MarketData const *exchange1, const int fee1, MarketData const *exchange2, const int fee2);
  void buy(MarketData const *data);
  void sell(MarketData const *data);
  Logger *logger;
};

#pragma once

#include <stdio.h>
#include <unordered_map>
#include <string>

#include "../ordering-system/OrderExecutor.h"
#include "MarketData.h"

using namespace std;

class TradingStrategy {
 public:
  void updateData(MarketData &);
  virtual void runStrategy() = 0;
  virtual void buy(MarketData &);
  virtual void sell(MarketData &);

 protected:
  unordered_map<Exchange::ExchangeName, MarketData&, hash<int>> exchangeData;
  OrderExecutor orderExecutor;
};
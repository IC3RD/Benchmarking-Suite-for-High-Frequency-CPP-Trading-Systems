#pragma once

#include <stdio.h>

#include <string>
#include <unordered_map>

#include "MarketData.h"
#include "OrderManager.h"
#include "dataManager/OrderBook.h"

using namespace std;

class TradingStrategy {
 public:
  void updateData(MarketData &);
  virtual void runStrategy() = 0;
  virtual void buy(MarketData &);
  virtual void sell(MarketData &);

 protected:
  unordered_map<Exchange::ExchangeName, MarketData &, hash<int>> exchangeData;
  OrderManager orderManager;
  OrderBook orderBook;
};
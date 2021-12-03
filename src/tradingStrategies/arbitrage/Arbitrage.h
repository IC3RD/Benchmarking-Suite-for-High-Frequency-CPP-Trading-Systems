#pragma once

#include <stdio.h>

#include <vector>

#include "dataManager/OrderBook.h"
#include "dataManager/OrderData.h"
#include "dataManager/OrderDataStore.h"
#include "tradingStrategies/TradingStrategy.h"

using namespace std;

class Arbitrage : public TradingStrategy {
 public:
  Arbitrage();
  ~Arbitrage();
  void runStrategy() override;
  virtual void newData(std::shared_ptr<OrderData>);

 private:
  void process(std::shared_ptr<OrderBook> exchange1Book,
               std::shared_ptr<OrderBook> exchange2Book);
  vector<Exchange::ExchangeName> exchanges;
};

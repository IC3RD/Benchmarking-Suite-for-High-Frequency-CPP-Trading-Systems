#pragma once

#include <stdio.h>

#include <vector>

#include "../TradingStrategy.h"
#include "dataManager/OrderBook.h"
#include "dataManager/OrderDataStore.h"
#include "exchange/OrderData.h"

using namespace std;

class Arbitrage : public TradingStrategy {
 public:
  Arbitrage();
  ~Arbitrage();
  void runStrategy() override;

 private:
  void process(std::shared_ptr<OrderBook> exchange1Book, std::shared_ptr<OrderBook> exchange2Book);
  vector<Exchange::ExchangeName> exchanges;
};
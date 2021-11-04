#pragma once

#include <stdio.h>

#include <deque>

#include "../exchange/MarketData.h"
#include "../exchange/TradingStrategy.h"
#include "../ordering-system/OrderExecutor.h"

using namespace std;

class Arbitrage : public TradingStrategy {
 public:
  Arbitrage();

  ~Arbitrage();

  void runStrategy() override;

 private:
  void process(MarketData &, MarketData &);
  list<Exchange::ExchangeName> exchanges;
  OrderExecutor *orderExecutor;
};

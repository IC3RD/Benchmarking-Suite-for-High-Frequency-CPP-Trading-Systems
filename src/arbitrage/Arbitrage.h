#pragma once

#include <stdio.h>

#include <list>

#include "../exchange/MarketData.h"
#include "../exchange/TradingStrategy.h"

using namespace std;

class Arbitrage : public TradingStrategy {
 public:
  Arbitrage();
  ~Arbitrage();
  void runStrategy() override;

 private:
  void process(MarketData &, MarketData &);
  list<Exchange::ExchangeName> exchanges;
};

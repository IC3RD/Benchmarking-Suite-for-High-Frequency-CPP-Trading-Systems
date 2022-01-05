#pragma once
#include <stdio.h>

#include <unordered_map>

#include "Band.h"
#include "dataManager/Order.h"
#include "exchange/Exchange.h"
#include "ordering-system/OrderExecutor.h"
#include "tradingStrategies/TradingStrategy.h"

class BollingerBand : public TradingStrategy {
 public:
  BollingerBand();
  ~BollingerBand();
  void runStrategy();
  void newData(std::shared_ptr<OrderData>);
  void addExchange(Exchange::ExchangeName exchange);
  bool hasBand();

 private:
  std::unordered_map<Exchange::ExchangeName, std::shared_ptr<Band>>
      exchangeToBandMap;
};
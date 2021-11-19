#pragma once
#include <stdio.h>

#include <unordered_map>


#include "Band.h"
#include "exchange/Exchange.h"
#include "dataManager/Order.h"
#include "tradingStrategies/TradingStrategy.h"
#include "ordering-system/OrderExecutor.h"

class BollingerBand : public TradingStrategy {
 public:
  BollingerBand();
  ~BollingerBand();
  void runStrategy();
  void newData(std::shared_ptr<OrderData>);
  void addExchange(Exchange::ExchangeName exchange);

 private:
  std::unordered_map<Exchange::ExchangeName, std::shared_ptr<Band>>
      exchangeToBandMap;
};
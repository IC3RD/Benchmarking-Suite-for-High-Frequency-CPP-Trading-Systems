#pragma once

#include <json/single_include/nlohmann/json.hpp>

#include "dataManager/OrderBook.h"
#include "dataManager/OrderData.h"
#include "dataManager/OrderTypes.h"
#include "exchange/Exchange.h"

class OrderDataCollector {
 public:
  OrderDataCollector(OrderBook &, Exchange::ExchangeName);
  ~OrderDataCollector();
  void constructAndPassOrderData(OrderTypes::OrderType type, int price,
                                 double volume);

 protected:
  const Exchange::ExchangeName exchange;
  virtual void passJSON(nlohmann::json json) = 0;

 private:
  OrderBook &orderBook;
};
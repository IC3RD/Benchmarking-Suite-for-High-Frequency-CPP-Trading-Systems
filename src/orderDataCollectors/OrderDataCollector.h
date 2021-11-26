#pragma once

#include "dataManager/OrderBook.h"
#include "exchange/Exchange.h"
#include "exchange/OrderData.h"
#include "exchange/OrderTypes.h"

class OrderDataCollector {
 public:
  OrderDataCollector(OrderBook &, Exchange::ExchangeName);

  ~OrderDataCollector();

  void constructAndPassOrderData(OrderTypes::OrderType type, int price,
                                 double volume);

 protected:
  const Exchange::ExchangeName exchange;

 private:
  OrderBook &orderBook;
};
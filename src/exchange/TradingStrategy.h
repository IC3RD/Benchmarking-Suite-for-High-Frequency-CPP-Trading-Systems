#pragma once

#include <stdio.h>

#include <string>
#include <unordered_map>

#include "MarketData.h"
#include "OrderManager.h"
#include "dataManager/OrderBook.h"
#include "exchange/OrderData.h"

class OrderBook;

class TradingStrategy {
 public:
  virtual void newData(std::shared_ptr<OrderData>) = 0;
  virtual void runStrategy() = 0;
  virtual void buy(std::shared_ptr<OrderData>);
  virtual void sell(std::shared_ptr<OrderData>);
  void insertNewOrderBook(std::shared_ptr<OrderBook>);

 protected:
  unordered_map<Exchange::ExchangeName, std::shared_ptr<OrderBook>, hash<int>>
      exchangeOrderBooks;
  OrderManager orderManager;
};
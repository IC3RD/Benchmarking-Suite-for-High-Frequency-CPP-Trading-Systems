#pragma once
#include <unordered_map>
#include <vector>

#include "OrderExecutor.h"
#include "binance/BinanceOrderExecutor.h"
#include "bitmex/BitmexOrderExecutor.h"
#include "coinbase/CoinbaseOrderExecutor.h"
#include "exchange/Exchange.h"
#include "exchange/Order.h"

class OrderManager {
 public:
  OrderManager();
  void submitOrder(Exchange::ExchangeName exchange, const Order &order);

 private:
  std::vector<Order> *portfolio;
  std::unordered_map<Exchange::ExchangeName, OrderExecutor *>
      orderExecutors;
};

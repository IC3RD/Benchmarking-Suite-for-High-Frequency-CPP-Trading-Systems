#pragma once
#include "OrderExecutor.h"
#include "binance/BinanceOrderExecutor.h"
#include "bitmex/BitmexOrderExecutor.h"
#include "coinbase/CoinbaseOrderExecutor.h"
#include "exchange/Exchange.h"
#include "exchange/Order.h"

#include <unordered_map>
#include <vector>

class OrderManager {
 public:
  OrderManager();
  void submitOrder(Exchange::ExchangeName exchange, const Order &order);

 private:
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange::ExchangeName, OrderExecutor *>
      orderExecutors;
};

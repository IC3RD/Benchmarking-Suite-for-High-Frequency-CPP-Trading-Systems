#pragma once
#include <dataManager/Order.h>
#include <exchange/Exchange.h>
#include <ordering-system/OrderExecutor.h>
#include <ordering-system/exchangeExecutors/binance/BinanceOrderExecutor.h>
#include <ordering-system/exchangeExecutors/bitmex/BitmexOrderExecutor.h>
#include <ordering-system/exchangeExecutors/coinbase/CoinbaseOrderExecutor.h>

#include <unordered_map>
#include <vector>

class OrderManager {
 public:
  OrderManager();
  // Track order and then pass to an OrderExecutor.
  void submitOrder(Exchange::ExchangeName exchange, Order order);

 private:
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange::ExchangeName, OrderExecutor *>
      orderExecutors;
};

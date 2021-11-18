#pragma once
#include <OrderExecutor.h>
#include <exchange/Exchange.h>
#include <exchange/Order.h>
#include <exchangeExecutors/binance/BinanceOrderExecutor.h>
#include <exchangeExecutors/bitmex/BitmexOrderExecutor.h>
#include <exchangeExecutors/coinbase/CoinbaseOrderExecutor.h>

#include <unordered_map>
#include <vector>

class OrderManager {
  // Algorithm
 public:
  OrderManager();
  // Track order and then pass to an OrderExecutor.
  void submitOrder(Exchange::ExchangeName exchange, Order order);

 private:
  //  std::unordered_map<int, Order> *pendingOrders;
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange::ExchangeName, OrderExecutor *>
      orderExecutors;
};

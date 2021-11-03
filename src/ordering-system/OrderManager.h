#pragma once
#include <Exchange.h>
#include <Order.h>
#include <OrderExecutor.h>
#include <binance/BinanceOrderExecutor.h>
#include <bitmex/BitmexOrderExecutor.h>
#include <coinbase/CoinbaseOrderExecutor.h>
#include <unordered_map>
#include <vector>

class OrderManager {
  // Algorithm
 public:
  OrderManager();
  // Track order and then pass to an OrderExecutor.
  void submitOrder(Order order);

 private:
//  std::unordered_map<int, Order> *pendingOrders;
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange, OrderExecutor *> orderExecutors;
};

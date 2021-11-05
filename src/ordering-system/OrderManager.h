#pragma once
#include <vector>
#include <unordered_map>

#include "exchange/Order.h"
#include "OrderBuilder.h"
#include "OrderExecutor.h"

class OrderManager {
public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return OrderBuilder(); }
  OrderManager();
  virtual std::string getURL() = 0;
  virtual std::string getExchangeName() = 0;

 private:
//  std::unordered_map<int, Order> *pendingOrders;
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange, OrderExecutor *> orderExecutors;
};

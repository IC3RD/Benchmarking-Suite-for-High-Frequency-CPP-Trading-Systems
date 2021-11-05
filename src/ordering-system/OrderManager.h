#pragma once

#include "../exchange/Order.h"
#include "OrderBuilder.h"
using namespace std;
class OrderManager {
public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return OrderBuilder(); }
  OrderManager(){};
  virtual string getURL() = 0;
  virtual string getExchangeName() = 0;

 private:
//  std::unordered_map<int, Order> *pendingOrders;
  std::vector<Order> *portfolio;
  const std::unordered_map<Exchange, OrderExecutor *> orderExecutors;
};

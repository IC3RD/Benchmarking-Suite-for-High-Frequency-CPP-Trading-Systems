#pragma once
#include <OrderBuilder.h>
#include <exchange/Order.h>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual std::string getDestination() = 0;
};
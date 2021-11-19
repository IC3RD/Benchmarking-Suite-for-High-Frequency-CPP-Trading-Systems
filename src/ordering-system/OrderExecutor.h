#pragma once
#include <dataManager/Order.h>
#include <ordering-system/OrderBuilder.h>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual std::string getDestination() = 0;
};
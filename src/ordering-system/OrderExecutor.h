#pragma once
#include <ordering-system/OrderBuilder.h>
#include <dataManager/Order.h>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual std::string getDestination() = 0;
};
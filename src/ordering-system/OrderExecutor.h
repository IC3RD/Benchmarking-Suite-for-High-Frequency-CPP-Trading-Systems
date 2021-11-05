#pragma once
#include <OrderBuilder.h>
#include <exchange/Order.h>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual std::string getURL() = 0;
  virtual std::string getExchangeName() = 0;

 private:
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;
};
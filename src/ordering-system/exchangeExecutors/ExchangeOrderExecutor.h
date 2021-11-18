#pragma once
#include <exchange/Order.h>
#include <ordering-system/OrderExecutor.h>

class ExchangeOrderExecutor : public OrderExecutor {
 public:
  ExchangeOrderExecutor() = default;
  virtual void submitOrder(Order order) = 0;
  virtual std::string getDestination() = 0;
  virtual std::string getExchangeName() = 0;

 private:
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;
};
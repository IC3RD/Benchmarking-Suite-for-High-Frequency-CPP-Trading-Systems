#pragma once
#include <OrderBuilder.h>
#include <exchange/Order.h>
#include <curl/curl.h>
#include <iostream>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual std::string getURL() = 0;
  virtual std::string getExchangeName() = 0;
  void enableBenchmarking();
  void disableBenchmarking();

 private:
  bool benchmark = false;
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;

 protected:
  void sendOrder(CURL *curl);
};
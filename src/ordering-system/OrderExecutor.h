#pragma once
#include <OrderBuilder.h>
#include <exchange/Order.h>
#include <curl/curl.h>
#include <iostream>

#define PRINT(x)                 \
  do {                           \
    std::cout << x << std::endl; \
  } while (0)

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
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;

 protected:
  void sendOrder(CURL *curl);
  bool benchmark = false;
  bool output = true;
  void enableOutput();
  void disableOutput();
};
#pragma once
#include <curl/curl.h>

#include <iostream>

#include "exchange/Order.h"

#define PRINT(x)                 \
  do {                           \
    std::cout << x << std::endl; \
  } while (0)

class OrderExecutor {
 public:
  OrderExecutor(std::string secret_key, std::string public_key);

  virtual void submitOrder(Order order) = 0;

  /* Stores URL and Exchange Name in implementation. */
  virtual std::string getURL() = 0;
  virtual std::string getExchangeName() = 0;

  void enableBenchmarking();
  void disableBenchmarking();
  void enableOutput();
  void disableOutput();

  void printOrderDetails(const std::string& order_data);

 private:
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;

 protected:
  std::string secret_key;
  std::string public_key;
  void sendOrder(CURL *curl);
  bool benchmark = false;
  bool output = true;
};
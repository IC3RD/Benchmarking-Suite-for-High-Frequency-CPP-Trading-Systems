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
  OrderExecutor() = default;

  virtual void submitOrder(Order order) = 0;

  /* Stores URL and Exchange Name in implementation. */
  virtual std::string getURL() = 0;

  virtual std::string getExchangeName() = 0;

  void enableBenchmarking();

  void disableBenchmarking();

  void enableOutput();

  void disableOutput();

 private:
  virtual std::string getSecretKey() = 0;

  virtual std::string getPublicKey() = 0;

 protected:
  void sendOrder(CURL *curl);

  bool benchmark = false;
  bool output = true;
};
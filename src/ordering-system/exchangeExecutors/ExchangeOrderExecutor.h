#pragma once
#include <dataManager/Order.h>
#include <ordering-system/OrderExecutor.h>

#include <memory>

#include "utils/CurlManager.h"

#define PRINT(x)                 \
  do {                           \
    std::cout << x << std::endl; \
  } while (0)

class ExchangeOrderExecutor : public OrderExecutor {
 public:
  ExchangeOrderExecutor();
  void enableOutput();
  void disableOutput();

 private:
  virtual std::string getSecretKey() = 0;
  virtual std::string getPublicKey() = 0;

 protected:
  void sendOrder();
  bool output = true;
  std::unique_ptr<CurlManager> curlManager;
};
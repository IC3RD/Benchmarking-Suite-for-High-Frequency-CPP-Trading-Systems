#pragma once
#include <curl/curl.h>
#include <dataManager/Order.h>
#include <ordering-system/OrderExecutor.h>

#define PRINT(x)                 \
  do {                           \
    std::cout << x << std::endl; \
  } while (0)

#ifdef BENCHMARK_CPP_TEST
#include "../../../benchmarking/mocks/mockCurl.h"
#else
//#include <curl/curl.h>
#endif



class ExchangeOrderExecutor : public OrderExecutor {
 public:
  ExchangeOrderExecutor() = default;
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
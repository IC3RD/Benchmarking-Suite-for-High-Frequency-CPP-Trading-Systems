//
// Created by Jake Dickie on 28/10/2021.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H
#define CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H

#include <ordering-system/OrderBuilder.h>
#include <ordering-system/exchangeExecutors/ExchangeOrderExecutor.h>

class CoinbaseOrderExecutor : public ExchangeOrderExecutor {
 public:
  CoinbaseOrderExecutor();
  void submitOrder(Order order) override;
  std::string getDestination() override;
  std::string getExchangeName() override;

 private:
  static std::string parseOrder(const Order &order);
  std::string authenticate(const std::string &message,
                           const std::string &timestamp);
  static std::string generateTimestamp();
  void generateHeaders(struct curl_slist **chunk, const std::string &data);
  std::string getSecretKey() override;
  std::string getPublicKey() override;
  static std::string hex_to_string(const std::string &in);
};

#endif  // CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H

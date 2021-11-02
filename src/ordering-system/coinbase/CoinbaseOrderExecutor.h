//
// Created by Jake Dickie on 28/10/2021.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H
#define CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H

#include <OrderBuilder.h>
#include <OrderExecutor.h>

class CoinbaseOrderExecutor : public OrderExecutor {
public:
  CoinbaseOrderExecutor();
  void submitOrder(Order order) override;
  string getURL() override;
  string getExchangeName() override;

private:
  static string parseOrder(const Order &order);
  string authenticate(const string &message, const string &timestamp);
  static string generateTimestamp();
  void generateHeaders(struct curl_slist **chunk, const string &data);
  string getSecretKey() override;
  string getPublicKey() override;
  static std::string hex_to_string(const std::string &in);
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDEREXECUTOR_H

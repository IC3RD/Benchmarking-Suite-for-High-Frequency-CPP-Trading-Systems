//
// Created by Jake Dickie on 28/10/2021.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H

#include <OrderBuilder.h>
#include <OrderManager.h>

class CoinbaseOrderManager : public OrderManager {
public:
  CoinbaseOrderManager();
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

#endif // CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H

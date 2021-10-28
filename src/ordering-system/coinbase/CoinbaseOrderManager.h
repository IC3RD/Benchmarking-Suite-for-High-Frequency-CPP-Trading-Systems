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

private:
  string parseOrder(Order order);
  string authenticate(string message, string timestamp);
  string generateTimestamp();
  void generateHeaders(struct curl_slist **chunk, string data);
  string getSecretKey();
  string getPublicKey();
  static std::string base64_encode(const std::string &in);
  static std::string base64_decode(const std::string &in);

};

#endif // CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H

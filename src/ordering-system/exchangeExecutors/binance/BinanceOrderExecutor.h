//
// Created by panos on 10/29/21.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDEREXECUTOR_H
#define CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDEREXECUTOR_H

#include <OrderBuilder.h>
#include <ExchangeOrderExecutor.h>

class BinanceOrderExecutor : public ExchangeOrderExecutor {
 public:
  BinanceOrderExecutor();
  void submitOrder(Order order) override;
  std::string getDestination() override;
  std::string getExchangeName() override;

 private:
  std::string parseOrder(const Order& order);
  std::string authenticate(std::string message);
  std::string generateTimestamp();
  void generateHeaders(struct curl_slist** chunk);
  std::string getSecretKey() override;
  std::string getPublicKey() override;
};

#endif  // CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDEREXECUTOR_H

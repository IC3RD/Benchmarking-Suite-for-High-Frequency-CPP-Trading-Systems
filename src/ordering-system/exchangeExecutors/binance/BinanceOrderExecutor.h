#pragma once
#include <ordering-system/OrderBuilder.h>
#include <ordering-system/exchangeExecutors/ExchangeOrderExecutor.h>

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
  void generateHeaders();
  std::string getSecretKey() override;
  std::string getPublicKey() override;
};

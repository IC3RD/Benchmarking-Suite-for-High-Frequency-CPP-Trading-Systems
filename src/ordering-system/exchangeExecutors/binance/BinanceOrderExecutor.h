#pragma once
#include <ordering-system/OrderBuilder.h>
#include <ordering-system/exchangeExecutors/ExchangeOrderExecutor.h>

class BinanceOrderExecutor : public ExchangeOrderExecutor {
 public:
  BinanceOrderExecutor();
  void submitOrder(Order order) override;
  std::string getDestination() override;
  std::string getExchangeName() override;
  // TODO: Below were private before, but I made them public for benchmarking.
  std::string parseOrder(const Order& order);
  std::string authenticate(std::string message);
  std::string generateTimestamp();
  void generateHeaders();

 private:
  std::string getSecretKey() override;
  std::string getPublicKey() override;
};

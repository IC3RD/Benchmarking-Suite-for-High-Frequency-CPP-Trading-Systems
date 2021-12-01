#pragma once
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
  void generateHeaders(const std::string &data);
  std::string getSecretKey() override;
  std::string getPublicKey() override;
  static std::string hex_to_string(const std::string &in);
};

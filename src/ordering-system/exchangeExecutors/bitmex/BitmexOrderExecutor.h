#pragma once
#include <ordering-system/exchangeExecutors/ExchangeOrderExecutor.h>
class BitmexOrderExecutor : public ExchangeOrderExecutor {
 public:
  BitmexOrderExecutor();
  void submitOrder(Order order) override;
  std::string getDestination() override;
  std::string getExchangeName() override;
  static std::string parseOrder(const Order &order);

 private:
  std::string getSecretKey() override;
  std::string getPublicKey() override;
  void generateHeaders(const std::string &data);
  static std::string generateTimestamp();
  std::string generateSignature(const std::string &message,
                                const std::string &timestamp);
};

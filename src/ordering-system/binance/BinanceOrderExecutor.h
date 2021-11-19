#pragma once
#include "OrderExecutor.h"

class BinanceOrderExecutor : public OrderExecutor {
 public:
  BinanceOrderExecutor(std::string secret_key, std::string public_key);
  void submitOrder(Order order) override;
  std::string getURL() override;
  std::string getExchangeName() override;

 private:
  std::string parseOrder(const Order& order);
  std::string authenticate(std::string message);
  std::string generateTimestamp();
  void generateHeaders(struct curl_slist** chunk);
  std::string getSecretKey() override;
  std::string getPublicKey() override;
};

#pragma once
#include "OrderExecutor.h"

class CoinbaseOrderExecutor : public OrderExecutor {
 public:
  CoinbaseOrderExecutor(std::string secret_key, std::string public_key);
  void submitOrder(Order order) override;
  std::string getURL() override;
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
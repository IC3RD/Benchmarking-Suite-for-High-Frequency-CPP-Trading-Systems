#pragma once
#include "OrderExecutor.h"
class BitmexOrderExecutor : public OrderExecutor {
 public:
  BitmexOrderExecutor(std::string secret_key, std::string public_key);
  void submitOrder(Order order) override;
  std::string getURL() override;
  std::string getExchangeName() override;

 private:
  std::string getSecretKey() override;
  std::string getPublicKey() override;
  void generateHeaders(struct curl_slist **chunk, const std::string &data);
  static std::string parseOrder(const Order &order);
  static std::string generateTimestamp();
  std::string generateSignature(const std::string &message,
                                const std::string &timestamp);
};

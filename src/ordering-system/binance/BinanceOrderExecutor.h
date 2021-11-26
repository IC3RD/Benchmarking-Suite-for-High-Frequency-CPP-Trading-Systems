#pragma once

#include "OrderExecutor.h"

class BinanceOrderExecutor : public OrderExecutor {
 public:
  BinanceOrderExecutor();

  void submitOrder(Order order) override;

  std::string getURL() override;

  std::string getExchangeName() override;

  std::string parseOrder(
      const Order &order);  // these were private if we figure how to mock curl
                            // we should make
  std::string authenticate(const std::string &message);  // them private again
  void generateHeaders(struct curl_slist **chunk);       // this too
 private:
  std::string generateTimestamp();

  std::string getSecretKey() override;

  std::string getPublicKey() override;
};

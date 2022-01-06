;
#pragma once
#include <stdio.h>

#include <string>

#include "exchange/Exchange.h"

class Order {
 public:
  Order(std::string, long long, int, bool);
  Order(std::string symbol, long long price, int volume, bool isBuyOrder,
        Exchange::ExchangeName exchange);
  int getVolume() const;
  long long getPrice() const;
  bool isBuyOrder() const;
  std::string getSymbol() const;
  Exchange::ExchangeName getExchange();
  void setExchange(Exchange::ExchangeName exchange);

 private:
  Exchange::ExchangeName exchange;
  const std::string symbol;
  const long long price;
  const int volume;
  const bool isBuy;  // If not it is a sell order
};

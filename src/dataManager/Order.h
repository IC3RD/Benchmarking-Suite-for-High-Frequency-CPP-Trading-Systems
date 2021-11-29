;
#pragma once
#include <stdio.h>

#include <string>

#include "exchange/Exchange.h"

class Order {
 public:
  Order(std::string, int, int, bool);
  Order(std::string symbol, int price, int volume, bool isBuyOrder,
        Exchange::ExchangeName exchange);
  int getVolume() const;
  int getPrice() const;
  bool isBuyOrder() const;
  std::string getSymbol() const;
  Exchange::ExchangeName getExchange();
  void setExchange(Exchange::ExchangeName exchange);

 private:
  Exchange::ExchangeName exchange;
  const std::string symbol;
  const int price;
  const int volume;
  const bool isBuy;  // If not it is a sell order
};

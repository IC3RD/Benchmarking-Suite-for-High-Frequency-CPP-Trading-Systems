;
#pragma once
#include "Exchange.h"
#include <stdio.h>

#include <string>

class Order {
 public:
  Order(std::string, int, int, bool);
  Order(std::string symbol, int price, int volume, bool isBuyOrder,
        Exchange exchange);
  int getVolume() const;
  int getPrice() const;
  bool isBuyOrder() const;
  std::string getSymbol() const;
  Exchange getExchange();
  void setExchange(Exchange exchange);

 private:
  Exchange exchange;
  const std::string symbol;
  const int price;
  const int volume;
  const bool isBuy;  // If not it is a sell order
};

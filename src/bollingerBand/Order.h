#pragma once

#include <stdio.h>

#include <string>

class Order {
 public:
  Order(std::string, int, int, bool);
  int getVolume() const;
  int getPrice() const;
  bool isBuyOrder() const;
  std::string getSymbol() const;

 private:
  const std::string symbol;
  const int price;
  const int volume;
  const bool isBuy;  // If not it is a sell order
};

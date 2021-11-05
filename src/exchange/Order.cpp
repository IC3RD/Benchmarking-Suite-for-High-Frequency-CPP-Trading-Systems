#include "Order.h"

#include <ordering-system/Exchange.h>

#include <iostream>
#include <map>

Order::Order(const std::string s, int p, int v, bool isBuy)
    : symbol(s), price(p), volume(v), isBuy(isBuy){};

int Order::getVolume() const { return volume; }

int Order::getPrice() const { return price; }

std::string Order::getSymbol() const { return symbol; }

bool Order::isBuyOrder() const { return isBuy; }

Exchange Order::getExchange() {
  return this->exchange;
}

Order::Order(std::string symbol, int price, int volume, bool isBuyOrder,
             Exchange exchange)
    : Order(symbol, price, volume, isBuyOrder) {
  this->setExchange(exchange);
}
void Order::setExchange(Exchange exchange) {
  this->exchange = exchange;
}

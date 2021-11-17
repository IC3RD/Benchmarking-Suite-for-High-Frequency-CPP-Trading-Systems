#pragma once

#include "OrderTypes.h"

class OrderData {
 public:
  OrderData(OrderTypes::OrderType type, long price, double volume);
  ~OrderData();
  const OrderTypes::OrderType getOrderType() const;
  const long getOrderPrice() const;
  const double getOrderVolume() const;

 private:
  const OrderTypes::OrderType orderType;
  const long orderPrice;
  const double orderVolume;
};
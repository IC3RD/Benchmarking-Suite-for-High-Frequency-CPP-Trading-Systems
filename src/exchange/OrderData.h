#pragma once

#include "Exchange.h"
#include "OrderTypes.h"

class OrderData {
 public:
  OrderData(OrderTypes::OrderType type, Exchange::ExchangeName name, long price,
            double volume);
  ~OrderData();
  const OrderTypes::OrderType getOrderType() const;
  const Exchange::ExchangeName getExchange() const;
  const long getOrderPrice() const;
  const double getOrderVolume() const;

 private:
  const OrderTypes::OrderType orderType;
  const Exchange::ExchangeName exchange;
  const long orderPrice;
  const double orderVolume;
};
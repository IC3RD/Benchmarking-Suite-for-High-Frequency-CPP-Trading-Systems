#pragma once

#include "OrderTypes.h"
#include "exchange/Exchange.h"

class OrderData {
 public:
  OrderData(OrderTypes::OrderType type, Exchange::ExchangeName name,
            long long price, double volume);
  ~OrderData();
  const OrderTypes::OrderType getOrderType() const;
  const Exchange::ExchangeName getExchange() const;
  const long long getOrderPrice() const;
  const double getOrderVolume() const;

 private:
  const OrderTypes::OrderType orderType;
  const Exchange::ExchangeName exchange;
  const long long orderPrice;
  const double orderVolume;
};
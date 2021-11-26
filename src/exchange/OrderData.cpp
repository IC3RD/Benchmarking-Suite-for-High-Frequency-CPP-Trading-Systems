#include "OrderData.h"

OrderData::OrderData(OrderTypes::OrderType type,
                     Exchange::ExchangeName exchange, long price, double volume)
    : orderType(type),
      exchange(exchange),
      orderPrice(price),
      orderVolume(volume){};

OrderData::~OrderData(){};

const OrderTypes::OrderType OrderData::getOrderType() const {
  return orderType;
}

const Exchange::ExchangeName OrderData::getExchange() const { return exchange; }

const double OrderData::getOrderVolume() const { return orderVolume; }

const long OrderData::getOrderPrice() const { return orderPrice; }
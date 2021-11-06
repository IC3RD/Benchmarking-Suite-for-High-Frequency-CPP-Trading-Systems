#include "OrderData.h"

OrderData::OrderData(OrderTypes::OrderType type, int price, double volume) : orderType(type), orderPrice(price), orderVolume(volume) {};

OrderData::~OrderData() {};

const OrderTypes::OrderType OrderData::getOrderType() const {
    return orderType;
}

const double OrderData::getOrderVolume() const {
    return orderVolume;
}

const int OrderData::getOrderPrice() const {
    return orderPrice;
}
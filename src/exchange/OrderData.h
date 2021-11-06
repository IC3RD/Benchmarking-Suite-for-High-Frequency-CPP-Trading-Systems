#pragma once

#include "OrderTypes.h"

class OrderData {
    public:
        OrderData(OrderTypes::OrderType type, int price, double volume);
        ~OrderData();
        const OrderTypes::OrderType getOrderType() const;
        const int getOrderPrice() const;
        const double getOrderVolume() const;
    private:
        const OrderTypes::OrderType orderType;
        const int orderPrice;
        const double orderVolume;
};
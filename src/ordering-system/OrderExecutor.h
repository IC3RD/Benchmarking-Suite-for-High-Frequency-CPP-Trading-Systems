#pragma once
#include <memory>

#include "exchange/Order.h"
#include "OrderManager.h"
#include "exchange/Exchange.h"

class OrderExecutor {
public:
    OrderExecutor();
    void placeOrder(Exchange::ExchangeName exchange, Order order);
private:
    std::unique_ptr<OrderManager> coinbaseManager;
    std::unique_ptr<OrderManager> bitmexManager;
    //TODO: add extra managers for the different exchanges
};

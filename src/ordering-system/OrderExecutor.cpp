#include "OrderExecutor.h"
#include "exchange/Exchange.h"
#include "OrderManager.h"
#include "bitmex/BitmexOrderManager.h"
#include "coinbase/CoinbaseOrderManager.h"

OrderExecutor::OrderExecutor() {
    bitmexManager = std::make_unique<CoinbaseOrderManager>();
    coinbaseManager = std::make_unique<CoinbaseOrderManager>();
};

void OrderExecutor::placeOrder(Exchange::ExchangeName exchange, Order order) {
    switch (exchange) {
        case Exchange::BITMEX:
            bitmexManager->submitOrder(order);
            break;
        case Exchange::COINBASE:
            coinbaseManager->submitOrder(order);
            break;
        case Exchange::BINANCE:
            break;
        case Exchange::FTX:
            break;
        case Exchange::KRAKEN:
            break;
        default:
            break;
    }
}



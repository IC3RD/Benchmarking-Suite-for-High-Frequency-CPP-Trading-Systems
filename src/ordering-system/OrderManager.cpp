#include "OrderManager.h"

#include "exchange/Exchange.h"

OrderManager::OrderManager()
    : orderExecutors({{Exchange::BINANCE, new BinanceOrderExecutor()},
                      {Exchange::BITMEX, new BitmexOrderExecutor()},
                      {Exchange::COINBASE, new CoinbaseOrderExecutor()}}) {
  portfolio = new std::vector<Order>();
}

void OrderManager::submitOrder(Exchange::ExchangeName exchange, Order order) {
  ExchangeOrderExecutor* executor = orderExecutors.at(exchange);
  executor->enableOutput();
  executor->submitOrder(order);
  portfolio->push_back(order);
}

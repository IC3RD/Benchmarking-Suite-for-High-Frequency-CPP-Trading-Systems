//
// Created by Jake Dickie on 03/11/2021.
//

#include "OrderManager.h"
#include "OrderExecutor.h"

OrderManager::OrderManager()
    : orderExecutors({{BINANCE, new BinanceOrderExecutor()},
                      {BITMEX, new BitmexOrderExecutor()},
                      {COINBASE, new CoinbaseOrderExecutor()}}) {
  portfolio = new std::vector<Order>();
}

// TODO: add order_ids returned from exchanges to order class after
//  successful order.
void OrderManager::submitOrder(Order order) {
  OrderExecutor *executor = orderExecutors.at(order.getExchange());
  executor->submitOrder(order);
  portfolio->push_back(order);
}

//
// Created by Jake Dickie on 03/11/2021.
//

#include "OrderManager.h"
#include <thread>
#include <iostream>

OrderManager::OrderManager()
    : orderExecutors({{Exchange::BINANCE, new BinanceOrderExecutor()},
                      {Exchange::BITMEX, new BitmexOrderExecutor()},
                      {Exchange::COINBASE, new CoinbaseOrderExecutor()}}) {
  portfolio = new std::vector<Order>();
}

// TODO: add order_ids returned from exchanges to order class after
//  successful order.
void OrderManager::submitOrder(Exchange::ExchangeName exchange, Order order) {
  std::cout << "Thread submitting order: " << std::this_thread::get_id() <<
      std::endl;
  OrderExecutor *executor = orderExecutors.at(exchange);
  executor->submitOrder(order);
  portfolio->push_back(order);
}

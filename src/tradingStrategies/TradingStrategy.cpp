#pragma once

#include "TradingStrategy.h"

#include <iostream>
#include <utility>

void TradingStrategy::insertNewOrderBook(std::shared_ptr<OrderBook> book) {
  exchangeOrderBooks.insert(std::make_pair(book->getExchange(), book));
}

void TradingStrategy::executeBuy(std::shared_ptr<OrderData> data) {
  //  std::cout << "Buy\n";
  orderManager.submitOrder(
      data->getExchange(),
      Order("BTC", data->getOrderPrice(), data->getOrderVolume(), true));
}

void TradingStrategy::executeSell(std::shared_ptr<OrderData> data) {
  //  std::cout << "Sell\n";
  orderManager.submitOrder(
      data->getExchange(),
      Order("BTC", data->getOrderPrice(), data->getOrderVolume(), false));
}

// If benchmarking is enabled, don't actually execute the order.
// We instead define the functionality in executeBuy/executeSell -
// this will enable us to still benchmark the execution.
void TradingStrategy::buy(std::shared_ptr<OrderData> data) {
#ifndef ENABLE_CPP_BENCHMARKS
  // Actually execute the buy
  executeBuy(std::move(data));
#endif
}

void TradingStrategy::sell(std::shared_ptr<OrderData> data) {
#ifndef ENABLE_CPP_BENCHMARKS
  // Actually execute the sell
  executeSell(std::move(data));
#endif
}

#include "TradingStrategy.h"

#include <iostream>
#include <utility>

void TradingStrategy::insertNewOrderBook(std::shared_ptr<OrderBook> book) {
  exchangeOrderBooks.insert(std::make_pair(book->getExchange(), book));
}

void TradingStrategy::executeBuy(std::shared_ptr<OrderData> data,
                                 bool testing) {
  //  std::cout << "Buy\n";
  orderManager.submitOrder(data->getExchange(),
                           Order("BTC", data->getOrderPrice(),
                                 data->getOrderVolume(), true, testing));
}

void TradingStrategy::executeSell(std::shared_ptr<OrderData> data,
                                  bool testing) {
  //  std::cout << "Sell\n";
  orderManager.submitOrder(data->getExchange(),
                           Order("BTC", data->getOrderPrice(),
                                 data->getOrderVolume(), false, testing));
}

// If benchmarking is enabled, don't actually execute the order.
// We instead define the functionality in executeBuy/executeSell -
// this will enable us to still benchmark the execution.
void TradingStrategy::buy(std::shared_ptr<OrderData> data) {
#ifndef ENABLE_CPP_BENCHMARKS
  // Actually execute the buy
  executeBuy(std::move(data), false);
#else
  executeBuy(std::move(data), true);
#endif
}

void TradingStrategy::sell(std::shared_ptr<OrderData> data) {
#ifndef ENABLE_CPP_BENCHMARKS
  // Actually execute the sell
  executeSell(std::move(data), false);
#else
  executeSell(std::move(data), true);
#endif
}

bool TradingStrategy::hasOrderBook() { return !exchangeOrderBooks.empty(); }

#pragma once

#include "TradingStrategy.h"

#include <iostream>
#include <string>

void TradingStrategy::insertNewOrderBook(std::shared_ptr<OrderBook> book) {
  exchangeOrderBooks.insert(std::make_pair(book->getExchange(), book));
}

void TradingStrategy::buy(std::shared_ptr<OrderData> data) {
  std::cout << "Buy\n";
  orderManager.submitOrder(
      data->getExchange(),
      Order("BTC", data->getOrderPrice(), data->getOrderVolume(), true));
}

void TradingStrategy::sell(std::shared_ptr<OrderData> data) {
  std::cout << "Sell\n";
  orderManager.submitOrder(
      data->getExchange(),
      Order("BTC", data->getOrderPrice(), data->getOrderVolume(), false));
}

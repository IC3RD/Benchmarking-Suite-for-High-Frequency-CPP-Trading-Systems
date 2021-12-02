#pragma once

#include "OrderDataCollector.h"

#include <memory>

#include "tradingStrategies/TradingStrategy.h"

OrderDataCollector::OrderDataCollector(OrderBook& orderBook,
                                       Exchange::ExchangeName exchange)
    : orderBook(orderBook), exchange(exchange) {}

OrderDataCollector::~OrderDataCollector() {}

void OrderDataCollector::constructAndPassOrderData(OrderTypes::OrderType type,
                                                   int price, double volume) {
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(type, exchange, price, volume);
  notifyTradingStrategies(data);
  orderBook.addEntry(data);
}

void OrderDataCollector::addTradingStrategy(
    std::shared_ptr<TradingStrategy> tradingStrategy) {
  listenerStrategies.push_back(tradingStrategy);
}

void OrderDataCollector::notifyTradingStrategies(
    std::shared_ptr<OrderData> data) {
  for (auto it = listenerStrategies.begin(); it != listenerStrategies.end();
       ++it) {
    (*it)->newData(data);
  }
}
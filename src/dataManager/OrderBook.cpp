#pragma once

#include "OrderBook.h"

OrderBook::OrderBook(Exchange::ExchangeName exchange) : exchange(exchange) {
  // these separate stores are causes errors for now
  bidStore = std::make_shared<OrderDataStore>();
  askStore = std::make_shared<OrderDataStore>();
}

OrderBook::~OrderBook() {}

void OrderBook::addTradingStrategy(
    std::shared_ptr<TradingStrategy> tradingStrategy) {
  listenerStrategies.push_back(tradingStrategy);
}

void OrderBook::addEntry(std::shared_ptr<OrderData> data) {
  switch (data->getOrderType()) {
    case (OrderTypes::ASK):
      askStore->addEntry(data);
    case (OrderTypes::BID):
      bidStore->addEntry(data);
  }
  for (auto it = listenerStrategies.begin(); it != listenerStrategies.end();
       ++it) {
    (*it)->newData(data);
  }
}

void OrderBook::sendOrder() {
  askStore->sendOrder();
  bidStore->sendOrder();
}

const Exchange::ExchangeName OrderBook::getExchange() const { return exchange; }

std::shared_ptr<OrderData> OrderBook::getHighestBid() {
  if (bidStore->isEmpty()) {
    return nullptr;
  }
  return bidStore->getLast();
}

std::shared_ptr<OrderData> OrderBook::getLowestAsk() {
  if (askStore->isEmpty()) {
    return nullptr;
  }
  return askStore->getFirst();
}

std::shared_ptr<OrderDataStore> OrderBook::getBidStore() { return bidStore; }

std::shared_ptr<OrderDataStore> OrderBook::getAskStore() { return askStore; }

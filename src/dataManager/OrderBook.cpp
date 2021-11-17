#pragma once

#include "OrderBook.h"

#include "bollingerBand/BollingerBand.h"

OrderBook::OrderBook(Exchange::ExchangeName exchange) : exchange(exchange) {
    // these separate stores are causes errors for now
    bidStore = std::make_unique<OrderDataStore>();
    askStore = std::make_unique<OrderDataStore>();
}

OrderBook::~OrderBook() {}

void OrderBook::addTradingStrategy(std::shared_ptr<TradingStrategy> tradingStrategy) {
  listenerStrategies.push_back(tradingStrategy);
}

void OrderBook::addEntry(std::shared_ptr<OrderData> data) {
  switch (data->getOrderType()) {
    case (OrderTypes::ASK):
      askStore->addEntry(data);
      if (data->getOrderPrice() < askStore->getBest()) {
        askStore->updateBest(data->getOrderPrice());
      }
    case (OrderTypes::BID):
      bidStore->addEntry(data);
      if (data->getOrderPrice() > bidStore->getBest()) {
        askStore->updateBest(data->getOrderPrice());
      }
  }
  for (auto it = listenerStrategies.begin(); it != listenerStrategies.end();
       ++it) {
    //(*it)->updateData(bidStore->);
  }
}

void OrderBook::sendOrder() {
    askStore->sendOrder();
    bidStore->sendOrder();
}
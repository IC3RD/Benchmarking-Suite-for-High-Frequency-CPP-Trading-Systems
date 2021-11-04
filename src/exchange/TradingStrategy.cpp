#pragma once

#include "TradingStrategy.h"

#include <iostream>
#include <string>

TradingStrategy::TradingStrategy() { 
  orderExecutor = new OrderExecutor(); 
  exchangeData = new unordered_map<Exchange::ExchangeName, MarketData&, hash<int>>();
  }

TradingStrategy::~TradingStrategy() {
    delete orderExecutor;
    delete exchangeData;
}

void TradingStrategy::updateData(MarketData& newData) {
  Exchange::ExchangeName exchange = newData.getExchange();
  auto itr = exchangeData->find(exchange);
  if (itr != exchangeData->end()) {
    if (newData.getBuyPrice() != -1) {
      (*itr).second.updateBuy(newData.getBuyPrice());
    }
    if (newData.getBuyVolume() != -1) {
      (*itr).second.updateBuyVolume(newData.getBuyVolume());
    }
    if (newData.getSellPrice() != -1) {
      (*itr).second.updateSell(newData.getSellVolume());
    }
    if (newData.getSellVolume() != -1) {
      (*itr).second.updateSellVolume(newData.getSellVolume());
    }
  } else {
    //auto pair = std::make_pair<Exchange::ExchangeName, MarketData&>(exchange, newData)
    exchangeData->insert({exchange, newData});
  }
  runStrategy();
}

void TradingStrategy::buy(MarketData& data) {
  std::cout << "Buy\n";
  orderExecutor->placeOrder(
      data.getExchange(),
      Order(data.getSymbol(), data.getBuyPrice(), 100, true));
}

void TradingStrategy::sell(MarketData& data) {
  std::cout << "Sell\n";
  orderExecutor->placeOrder(
      data.getExchange(),
      Order(data.getSymbol(), data.getSellPrice(), 100, false));
}

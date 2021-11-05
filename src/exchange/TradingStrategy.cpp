#pragma once

#include "TradingStrategy.h"

#include <iostream>
#include <string>

void TradingStrategy::updateData(MarketData& newData) {
  Exchange::ExchangeName exchange = newData.getExchange();
  auto itr = exchangeData.find(exchange);
  if (itr != exchangeData.end()) {
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
    exchangeData.insert({exchange, newData});
  }
  runStrategy();
}

void TradingStrategy::buy(MarketData& data) {
  std::cout << "Buy\n";
  orderManager.submitOrder(
      data.getExchange(),
      Order(data.getSymbol(), data.getBuyPrice(), 100, true));
}

void TradingStrategy::sell(MarketData& data) {
  std::cout << "Sell\n";
  orderManager.submitOrder(
      data.getExchange(),
      Order(data.getSymbol(), data.getSellPrice(), 100, false));
}

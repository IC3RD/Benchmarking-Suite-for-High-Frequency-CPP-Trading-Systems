#pragma once

#include <iostream>
#include <string>
#include "TradingStrategy.h"

TradingStrategy::TradingStrategy() {
    orderExecutor = new OrderExecutor();
}

void TradingStrategy::updateData(MarketData& newData){
    Exchange::ExchangeName exchange = newData.getExchange();
    auto itr = exchangeData.find(exchange);
    if (itr != exchangeData.end()){
        if (newData.getBuyPrice() != -1) {
            (*itr).updateBuyPrice(newData.getBuyPrice());
        }
        if (newData.getBuyVolume() != -1) {
            (*itr).updateBuyVolume(newData.getBuyVolume());
        }
        if (newData.getSellPrice() != -1) {
            (*itr).updateSellPrice(newData.getSellVolume());
        }
        if (newData.getSellVolume() != -1) {
            (*itr).updateSellVolume(newData.getSellVolume());
        }
        itr->second = newData;
    }else {
        exchangeData.insert(exchange, newData);
    }
    runStrategy();
}

void TradingStrategy::buy(MarketData& data) {
    std::cout << "Buy\n";
    orderExecutor.placeOrder(data.getExchange(), Order(data.getSymbol(), data.getBuyPrice(), 100, true));
}

void TradingStrategy::sell(MarketData& data) {
    std::cout << "Sell\n";
    orderExecutor.placeOrder(data.getExchange(), Order(data.getSymbol(), data.getSellPrice(), 100, false));
}

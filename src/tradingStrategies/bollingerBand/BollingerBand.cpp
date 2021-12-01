#include "BollingerBand.h"

#include <math.h>

#include <deque>
#include <iostream>

#include "Band.h"

BollingerBand::BollingerBand() {}
BollingerBand::~BollingerBand() {}

void BollingerBand::addExchange(Exchange::ExchangeName exchange) {
  exchangeToBandMap.insert(std::make_pair(exchange, std::make_shared<Band>()));
}

void BollingerBand::newData(std::shared_ptr<OrderData> newData) {
  auto it = exchangeToBandMap.find(newData->getExchange());
  if (it != exchangeToBandMap.end()) {
    // maybe this should not use the order price
    it->second->insertNewData(newData->getOrderPrice());
    runStrategy();
  }
}

void BollingerBand::runStrategy() {
  for (std::pair<Exchange::ExchangeName, std::shared_ptr<Band>> band :
       exchangeToBandMap) {
    auto it = exchangeOrderBooks.find(band.first);
    if (it != exchangeOrderBooks.end()) {
      std::shared_ptr<OrderBook> book = it->second;
      std::shared_ptr<OrderData> bestAsk = book->getHighestBid();
      std::shared_ptr<OrderData> bestBid = book->getLowestAsk();
      if (bestAsk != nullptr && bestBid != nullptr) {
        if (bestAsk->getOrderPrice() >
            band.second->getMean() + band.second->getStd()) {
          buy(bestAsk);
        }
        if (bestBid->getOrderPrice() <
            band.second->getMean() - band.second->getStd()) {
          sell(bestBid);
        }
      }
    }
  }
}

#include "Arbitrage.h"

#include <math.h>

#include <deque>
#include <iostream>

int bitmexFees = 0.0005;
int binanceFees = 0.00075;
int coinbaseFees = 0.03;  // fixed fee since we are trading at volume of 100
int volume = 100;
// this means only partial update from the exchange

Arbitrage::Arbitrage() : TradingStrategy() {
  exchanges = {Exchange::BITMEX, Exchange::COINBASE, Exchange::BINANCE};
}

Arbitrage::~Arbitrage() {}

void Arbitrage::runStrategy() {
  for (int i = 0; i < exchanges.size() - 1; ++i) {
    for (int j = i + 1; j < exchanges.size(); ++j) {
      process(exchangeOrderBooks.find(exchanges.at(i))->second,
              exchangeOrderBooks.find(exchanges.at(j))->second);
    }
  }
}

void Arbitrage::process(std::shared_ptr<OrderBook> exchange1Book,
                        std::shared_ptr<OrderBook> exchange2Book) {
  int fee1 = 0.01;
  int fee2 = 0.01;

  int exchange1SellPrice = exchange1Book->getHighestBid()->getOrderPrice();
  int exchange1BuyPrice = exchange1Book->getLowestAsk()->getOrderPrice();
  int exchange2SellPrice = exchange2Book->getHighestBid()->getOrderPrice();
  int exchange2BuyPrice = exchange2Book->getLowestAsk()->getOrderPrice();

  if (exchange1SellPrice > exchange2BuyPrice) {
    if (exchange1SellPrice * volume - exchange1SellPrice * volume * fee1 -
            exchange2BuyPrice * volume * fee2 >
        exchange2BuyPrice * volume) {
      if (exchange2Book->getAskAt(0)->getOrderVolume() < volume) {
        if (exchange1SellPrice > exchange2Book->getAskAt(1)->getOrderPrice()) {
          buy(exchange2Book->getAskAt(1));
          sell(exchange1Book->getHighestBid());
          // Since these are limit orders we will fill at the highest ask and
          // then continue buying at the lower price since there is still an
          // arbitrage opportunity
        }
      } else if (exchange1Book->getBidAt(0)->getOrderVolume() < volume) {
        if (exchange1Book->getBidAt(1)->getOrderPrice() > exchange2SellPrice) {
          buy(exchange2Book->getLowestAsk());
          sell(exchange1Book->getBidAt(1));
        }
      } else {
        sell(exchange1Book->getHighestBid());
        buy(exchange2Book->getLowestAsk());  // these should be market orders to
                                             // ensure fill
      }
    }
  } else if (exchange2SellPrice > exchange1BuyPrice) {
    if (exchange2SellPrice * volume - exchange2SellPrice * volume * fee2 -
            exchange1BuyPrice * volume * fee1 >
        exchange1BuyPrice * volume) {
      if (exchange1Book->getAskAt(0)->getOrderVolume() < volume) {
        if (exchange2SellPrice > exchange1Book->getAskAt(1)->getOrderPrice()) {
          buy(exchange1Book->getAskAt(1));
          sell(exchange2Book->getHighestBid());
          // Since these are limit orders we will fill at the highest ask and
          // then continue buying at the lower price since there is still an
          // arbitrage opportunity
        }
      } else if (exchange2Book->getBidAt(0)->getOrderVolume() < volume) {
        if (exchange2Book->getBidAt(1)->getOrderPrice() > exchange1SellPrice) {
          buy(exchange1Book->getLowestAsk());
          sell(exchange2Book->getBidAt(1));
        }
      } else {
        sell(exchange2Book->getHighestBid());
        buy(exchange1Book->getLowestAsk());  // these should be market orders to
                                             // ensure fill
      }
    }
  }
}

void Arbitrage::newData(std::shared_ptr<OrderData>){
    // TODO: Implement this? Or don't make this pure in TradingStrategy?
};

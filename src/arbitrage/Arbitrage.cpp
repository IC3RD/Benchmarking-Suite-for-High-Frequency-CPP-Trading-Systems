#include "Arbitrage.h"

#include <math.h>

#include <deque>
#include <iostream>

int bitmexFees = 0.0005;
int binanceFees = 0.00075;
int coinbaseFees = 0.03;  // fixed fee since we are trading at volume of 100
int volume = 100;
// todo: market data for each exchange and only update if value is not -1, as
// this means only partial update from the exchange

Arbitrage::Arbitrage() : TradingStrategy() {
  exchanges = {Exchange::BITMEX, Exchange::COINBASE, Exchange::BINANCE,
               Exchange::FTX, Exchange::KRAKEN};
}

Arbitrage::~Arbitrage() {}

void Arbitrage::runStrategy() {
  for (int i = 0; i < exchanges.size() - 1; ++i) {
    for (int j = i + 1; j < exchanges.size(); ++j) {
      process(exchangeData->find(exchanges.get(i)),
              exchangeData->find(exchanges.get(j)));
    }
  }
}

void Arbitrage::process(MarketData &exchange1, MarketData &exchange2) {
  int fee1 = exchange1.getFee();
  int fee2 = exchange2.getFee();
  int exchange1SellPrice = exchange1.getSellPrice();
  int exchange1BuyPrice = exchange1.getBuyPrice();
  int exchange2SellPrice = exchange2.getSellPrice();
  int exchange2BuyPrice = exchange2.getBuyPrice();
  if (exchange1SellPrice > exchange2BuyPrice) {
    if (exchange1SellPrice * volume - exchange1SellPrice * volume * fee1 -
            exchange2BuyPrice * volume * fee2 >
        exchange2BuyPrice * volume) {
      if (exchange2.getBuyVolume() < volume) {
        if (orderBook.getBidStore().getEntry(1).getOrderPrice() >
            exchange1SellPrice) {
          buy(orderBook.getBidStore().getEntry(1));
        }
      }
      if (exchange1.getSellVolume() < volume) {
        if (orderBook.getAskStore().getEntry(1).getOrderPrice() <
            exchange2BuyPrice) {
          sell(orderBook.getBidStore().getEntry(1));
        }
      }
      sell(exchange1);
      buy(exchange2);  // these should be market orders to ensure fill
    }
  } else if (exchange2SellPrice > exchange1BuyPrice) {
    if (exchange2SellPrice * volume - exchange2SellPrice * volume * fee1 -
            exchange1BuyPrice * volume * fee2 >
        exchange1BuyPrice * volume) {
      if (exchange1.getBuyVolume() < volume) {
        if (orderBook.getBidStore().getEntry(1).getOrderPrice() >
            exchange2SellPrice) {
          buy(orderBook.getBidStore().getEntry(1));
        }
      }
      if (exchange2.getSellVolume() < volume) {
        if (orderBook.getAskStore().getEntry(1).getOrderPrice() <
            exchange1BuyPrice) {
          sell(orderBook.getBidStore().getEntry(1));
        }
      }
      sell(exchange2);
      buy(exchange1);  // these should be market orders to ensure fill
    }
  }
};

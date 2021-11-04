#include "Arbitrage.h"

#include <math.h>
#include <deque>
#include <iostream>

#include "../exchange/MarketData.h"

int bitmexFees = 0.0005;
int binanceFees = 0.00075;
int coinbaseFees = 0.03; //fixed fee since we are trading at volume of 100
int volume = 100;
// TODO: market data for each exchange and only update if value is not -1, as this means only partial update from the exchange

Arbitrage::Arbitrage() : TradingStrategy() {
    exchanges = {
        Exchange::BITMEX,
        Exchange::COINBASE,
        Exchange::BINANCE,
        Exchange::FTX,
        Exchange::KRAKEN
    };
}

Arbitrage::~Arbitrage() {}

void Arbitrage::runStrategy() {
    for (int i = 0; i < exchanges.size() - 1; ++i) {
        for (int j = i + 1; j < exchanges.size(); ++j) {
            process(exchangeData.find(exchanges.get(i)), exchangeData.find(exchanges.get(j)));
        }
    }
}

void Arbitrage::process(MarketData& exchange1, MarketData& exchange2) {
    int fee1 = exchange1.getFee();
    int fee2 = exchange2.getFee();
    int exchange1SellPrice = exchange1.getSellPrice();
    int exchange1BuyPrice = exchange1.getBuyPrice();
    int exchange2SellPrice = exchange2.getSellPrice();
    int exchange2BuyPrice = exchange2.getBuyPrice();
    if (exchange1SellPrice > exchange2BuyPrice) {
        if (exchange1SellPrice * volume
            - exchange1SellPrice * volume * fee1
            - exchange2BuyPrice * volume * fee2 >
            exchange2BuyPrice * volume) {
            sell(exchange1);
            buy(exchange2); //these should be market orders to ensure fill
        }
    } else if (exchange2SellPrice > exchange1BuyPrice) {
        if (exchange2SellPrice * volume
            - exchange2SellPrice * volume * fee1
            - exchange1BuyPrice * volume * fee2 >
            exchange1BuyPrice * volume) {
            sell(exchange2);
            buy(exchange1); //these should be market orders to ensure fill
        }
    }
};


#include "Arbitrage.h"

#include <math.h>

#include <deque>
#include <iostream>

#include "Logger.h"
#include "MarketData.h"


using namespace std;
int bitmexFees = 0.0005;
int binanceFees = 0.00075;
int coinbaseFees = 0.03; //fixed fee since we are trading at volume of 100
int volume = 100;

Arbitrage::Arbitrage(int max) : maxElements(max) {
    orderExecutor = new OrderExecutor();
}

Arbitrage::~Arbitrage() {
    // delete logger;
}


void Arbitrage::strategy(list<MarketData> exchanges) {

    for (int i = 0; i < exchanges.size() - 1; ++i) {
        for (int j = i + 1; j < exchanges.size(); ++j) {
            process(exchanges.get(i), exchanges.get(j));
        }
    }

}

void Arbitrage::process(MarketData const *exchange1, MarketData const *exchange2) {
    fee1 = exchange1->getFee();
    fee2 = exchange2->getFee();
    exchange1SellPrice = exchange1->getSellPrice();
    exchange1BuyPrice = exchange1->getBuyPrice();
    exchange2SellPrice = exchange2->getSellPrice();
    exchange2BuyPrice = exchange2->getBuyPrice();
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
}

void Arbitrage::buy(MarketData const *data) {
    cout << "Buy\n";
    orderExecutor->placeOrder(Exchange.BITMEX, Order(data->getSymbol(), data->getBuyPrice(), 1, true));
}

void Arbitrage::sell(MarketData const *data) {
    cout << "Sell\n";
    orderExecutor->placeOrder(Exchange.BITMEX, Order(data->getSymbol(), data->getSellPrice(), 1, false));
}

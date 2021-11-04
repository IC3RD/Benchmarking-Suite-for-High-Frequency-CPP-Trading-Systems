#include "MarketData.h"

#include "../bollingerBand/BollingerBand.h"

MarketData::MarketData(const std::string s, int buy, int sell, int v, Exchange::ExchangeName exchangeName)
        : symbol(s),
          price((buy + sell) / 2),
          volume(v),
          sellPrice(sell),
          buyPrice(buy),
          tradingStrategy(new BollingerBand(100)),
          exchange(exchangeName),
          fee(0.0005){};
//todo:change exchange and to be whatever it is and put in constructor

MarketData::~MarketData() { delete tradingStrategy; }

const int MarketData::getVolume() const { return volume; }

const int MarketData::getPrice() const { return price; }

const int MarketData::getBuyPrice() const { return buyPrice; }

const int MarketData::getSellPrice() const { return sellPrice; }

const std::string MarketData::getSymbol() const { return symbol; }

//const Exchange::ExchangeName getExchange() { return exchange; }

//const int getFee() { return fee; }

BollingerBand *MarketData::getStrategy() const { return tradingStrategy; }

void MarketData::updateBuy(int b) {
    buyPrice = b;
    price = (sellPrice + buyPrice) / 2;
}

void MarketData::updateSell(int s) {
    sellPrice = s;
    price = (sellPrice + buyPrice) / 2;
}

void MarketData::updateVolume(int v) { volume = v; }

void MarketData::newMarketData() { tradingStrategy->strategy(this); }

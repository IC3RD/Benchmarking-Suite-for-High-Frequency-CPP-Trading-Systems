#include "MarketData.h"

#include "../bollingerBand/BollingerBand.h"

MarketData::MarketData(const std::string s, int buy, int sell, int buyVolume, int sellVolume, Exchange::ExchangeName exchangeName)
        : symbol(s),
          sellVolume(sellVolume),
          buyVolume(buyVolume),
          sellPrice(sell),
          buyPrice(buy),
          exchange(exchangeName),
          fee(0.0005) {};

//todo:change exchange and to be whatever it is and put in constructor

MarketData::~MarketData() {}

const int MarketData::getBuyVolume() const { return buyVolume; }

const int MarketData::getSellVolume() const { return sellVolume; }

const int MarketData::getPrice() const { return price; }

const int MarketData::getBuyPrice() const { return buyPrice; }

const int MarketData::getSellPrice() const { return sellPrice; }

const std::string MarketData::getSymbol() const { return symbol; }

const int MarketData::getFee() const { return fee; }

const Exchange::ExchangeName MarketData::getExchange() const { return exchange; }

void MarketData::updateBuy(int buy) {
    buyPrice = buy;
}

void MarketData::updateSell(int sell) {
    sellPrice = sell;
}

void MarketData::updateBuyVolume(int buyVol) {
    buyVolume = buyVol;
}

void MarketData::updateSellVolume(int sellVol) {
    sellVolume = sellVol;
}
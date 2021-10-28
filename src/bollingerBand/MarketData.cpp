#include "MarketData.h"

#include "BollingerBand.h"
using namespace std;

MarketData::MarketData(const string s, int buy, int sell, int v)
    : symbol(s),
      price((buy + sell) / 2),
      volume(v),
      sellPrice(sell),
      buyPrice(buy),
      tradingStrategy(new BollingerBand(100)){};

MarketData::~MarketData() { delete tradingStrategy; }

const int MarketData::getVolume() const { return volume; }

const int MarketData::getPrice() const { return price; }

const int MarketData::getBuyPrice() const { return buyPrice; }

const int MarketData::getSellPrice() const { return sellPrice; }

const string MarketData::getSymbol() const { return symbol; }

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

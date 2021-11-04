#pragma once

#include <stdio.h>
#include "Exchange.h"
#include <string>

using namespace std;

class BollingerBand;

class MarketData {
public:
  MarketData(string, int, int, int, Exchange::ExchangeName);
  ~MarketData();
  const int getVolume() const;
  const int getPrice() const;
  const int getBuyPrice() const;
  const int getSellPrice() const;
  const Exchange::ExchangeName getExchange() const;
  const int getFee() const;
  const std::string getSymbol() const;
  BollingerBand *getStrategy() const;
  void updateBuy(int);
  void updateSell(int);
  void updateVolume(int);
  void newMarketData();

private:
  const string symbol;
  int price;
  int volume;
  int sellPrice;
  int buyPrice;
  int fee;
  Exchange::ExchangeName exchange;
  BollingerBand *tradingStrategy;
};

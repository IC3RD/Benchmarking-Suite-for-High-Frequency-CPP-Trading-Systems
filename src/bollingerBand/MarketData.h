#pragma once

#include <stdio.h>

#include <string>

class BollingerBand;

class MarketData {
 public:
  MarketData(std::string, int, int, int);
  ~MarketData();
  const int getVolume() const;
  const int getPrice() const;
  const int getBuyPrice() const;
  const int getSellPrice() const;
  const std::string getSymbol() const;
  BollingerBand *getStrategy() const;
  void updateBuy(int);
  void updateSell(int);
  void updateVolume(int);
  void newMarketData();

 private:
  const std::string symbol;
  int price;
  int volume;
  int sellPrice;
  int buyPrice;
  BollingerBand *tradingStrategy;
};

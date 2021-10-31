#pragma once

#include <stdio.h>

#include <string>
#ifndef BAND
#define BAND
using namespace std;

class BollingerBand;

class MarketData {
public:
  MarketData(string, int, int, int);
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
  const string symbol;
  int price;
  int volume;
  int sellPrice;
  int buyPrice;
  BollingerBand *tradingStrategy;
};

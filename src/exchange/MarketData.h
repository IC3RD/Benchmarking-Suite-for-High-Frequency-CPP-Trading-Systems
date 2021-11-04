#pragma once

#include <stdio.h>

#include <string>

#include "Exchange.h"

using namespace std;

class MarketData {
 public:
  MarketData(string, int, int, int, int, Exchange::ExchangeName);
  ~MarketData();
  const int getSellVolume() const;
  const int getBuyVolume() const;
  const int getPrice() const;
  const int getBuyPrice() const;
  const int getSellPrice() const;
  const Exchange::ExchangeName getExchange() const;
  const int getFee() const;
  const std::string getSymbol() const;
  void updateSell(int);
  void updateBuy(int);
  void updateSellVolume(int);
  void updateBuyVolume(int);

 private:
  const string symbol;
  int price;
  int sellVolume;
  int sellPrice;
  int buyVolume;
  int buyPrice;
  int fee;
  const Exchange::ExchangeName exchange;
};

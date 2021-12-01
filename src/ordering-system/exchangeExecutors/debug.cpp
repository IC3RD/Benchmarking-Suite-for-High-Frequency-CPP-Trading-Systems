#include "debug.h"

#include <OrderExecutor.h>
#include <ordering-system/exchangeExecutors/binance/BinanceOrderExecutor.h>
#include <ordering-system/exchangeExecutors/bitmex/BitmexOrderExecutor.h>
#include <ordering-system/exchangeExecutors/coinbase/CoinbaseOrderExecutor.h>

#include <cstdio>
#include <iostream>
#include <memory>

int main() {
  DEBUG("Testing order system...");
  Order order{"BTC", 1, 1, true};
  auto bitmex = new BitmexOrderExecutor();
  bitmex->enableOutput();
  bitmex->submitOrder(order);
  delete bitmex;

  auto binance = new BinanceOrderExecutor();
  binance->enableOutput();
  binance->submitOrder(order);
  delete binance;
}
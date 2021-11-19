#include "debug.h"

#include <OrderExecutor.h>
#include <OrderManager.h>
#include <binance/BinanceOrderExecutor.h>
#include <bitmex/BitmexOrderExecutor.h>
#include <coinbase/CoinbaseOrderExecutor.h>
#include <stdlib.h>

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <memory>

#include "dotenv/dotenv.h"

int main() {
  //  std::string path{std::getenv("HOME")};
  //  path += "/API-KEYS.env";
  //  DEBUG(std::filesystem::exists(path));
  //  dotenv::init(path.c_str());
  //  DEBUG(dotenv::getenv("TESTVALUE"));

  OrderManager m{};
  Order order{"BTC", 57999, 100, false};
  m.submitOrder(Exchange::COINBASE, order);
  m.submitOrder(Exchange::BINANCE, order);
  m.submitOrder(Exchange::BITMEX, order);
}
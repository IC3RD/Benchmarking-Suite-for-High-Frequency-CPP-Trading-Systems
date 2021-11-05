#include "debug.h"

#include <OrderExecutor.h>
#include <OrderManager.h>
#include <binance/BinanceOrderExecutor.h>
#include <bitmex/BitmexOrderExecutor.h>
#include <coinbase/CoinbaseOrderExecutor.h>

#include <cstdio>
#include <iostream>
#include <memory>

int main() {
  DEBUG("Testing order system...");

  /* Sample class usage:
   * ExchangeAPIFactory factory {Exchange.Coinbase}; (Exchange.Coinbase is enum)
   * OrderExecutor manager = factory.createOrderManager();
   * // Since we haven't implemented a factory yet i'll just create an
   * // instance.
   */
  DEBUG("Creating order manager...");
  OrderManager manager{};
  Order order{"BTC", 1, 1, true};
  manager.submitOrder(Exchange::BITMEX, order);
  DEBUG("Did it work?");

  //  std::unique_ptr<OrderExecutor> coinbaseManager =
  //      std::make_unique<CoinbaseOrderExecutor>();
  //
  //  std::unique_ptr<OrderExecutor> manager =
  //      std::make_unique<BinanceOrderExecutor>();
  //
  //  OrderBuilder ob = coinbaseManager->createOrderBuilder();
  //
  //  ob.createBuyOrder(500);
  //  ob.addLimit(1);
  //  ob.amendVolume(100);
  //  ob.createBuyOrder(60000);
  //  ob.addLimit(52);
  //
  //  coinbaseManager->submitOrder(ob.toOrder());
  //
  //  std::unique_ptr<OrderExecutor> bitmex_manager =
  //      std::make_unique<BitmexOrderExecutor>();
  //  bitmex_manager->submitOrder(ob.toOrder());
}
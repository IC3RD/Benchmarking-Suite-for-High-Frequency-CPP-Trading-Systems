#include "debug.h"

#include <OrderManager.h>
#include <bitmex/BitmexOrderManager.h>
#include <coinbase/CoinbaseOrderManager.h>
#include <binance/BinanceOrderManager.h>
#include <cstdio>
#include <iostream>
#include <memory>

int main() {
  std::cout << "debug: Testing Order System..." << std::endl;

  /* Sample class usage:
   * ExchangeAPIFactory factory {Exchange.Coinbase}; (Exchange.Coinbase is enum)
   * OrderManager manager = factory.createOrderManager();
   * // Since we haven't implemented a factory yet i'll just create an
   * // instance.
   */

  std::unique_ptr<OrderManager> coinbaseManager =
      std::make_unique<CoinbaseOrderManager>();

  std::unique_ptr<OrderManager> manager =
      std::make_unique<BinanceOrderManager>();

  OrderBuilder ob = coinbaseManager->createOrderBuilder();

  ob.createBuyOrder(500);
  ob.addLimit(1);
  ob.amendVolume(100);
  ob.createBuyOrder(60000);
  ob.addLimit(52);

  coinbaseManager->submitOrder(ob.toOrder());

  std::unique_ptr<OrderManager> bitmex_manager =
      std::make_unique<BitmexOrderManager>();
  bitmex_manager->submitOrder(ob.toOrder());
}
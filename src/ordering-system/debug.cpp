#include "debug.h"

#include <OrderManager.h>
#include <coinbase/CoinbaseOrderManager.h>
#include <cstdio>
#include <iostream>
#include <memory>

int main() {
  std::cout << "debug: Testing Order System...";

  /* Sample class usage:
   * ExchangeAPIFactory factory {Exchange.Coinbase}; (Exchange.Coinbase is enum)
   * OrderManager manager = factory.createOrderManager();
   * // Since we haven't implemented a factory yet i'll just create an
   * // instance.
   */

  std::unique_ptr<OrderManager> manager =
      std::make_unique<CoinbaseOrderManager>();

  OrderBuilder ob = manager->createOrderBuilder();

  ob.createBuyOrder(500);
  ob.addLimit(1);
  ob.amendVolume(100);

  manager->submitOrder(ob.toOrder());
}
//
// Created by Jake Dickie on 28/10/2021.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H

#include <OrderBuilder.h>
#include <OrderManager.h>

class CoinbaseOrderManager : public OrderManager {
public:
  CoinbaseOrderManager();
  void submitOrder(Order order) override;
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_COINBASEORDERMANAGER_H

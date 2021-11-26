#pragma once
#include <curl/curl.h>
#include <dataManager/Order.h>
#include <ordering-system/OrderBuilder.h>

#include <iostream>

class OrderExecutor {
 public:
  virtual void submitOrder(Order order) = 0;
  OrderExecutor() = default;

  /* Stores URL and Exchange Name in implementation. */
  virtual std::string getExchangeName() = 0;

 protected:
  virtual std::string getDestination() = 0;
};
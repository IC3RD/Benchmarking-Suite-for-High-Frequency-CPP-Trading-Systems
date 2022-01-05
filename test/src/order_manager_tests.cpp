#include <iostream>
#include <string>

#include "dataManager/Order.h"
#include "gtest/gtest.h"
#include "ordering-system/OrderManager.h"

struct OrderManagerTests : public ::testing::Test {
  std::shared_ptr<OrderManager> orderManager;

  OrderManager& getManager() { return *orderManager; }

  virtual void SetUp() override {
    orderManager = std::make_shared<OrderManager>();
  }

  virtual void TearDown() override {}
};

TEST_F(OrderManagerTests, initialisedCorrectlyTest) {
  ASSERT_NE(&getManager(), nullptr);
}

// The purpose of these tests are to catch if anything goes wrong in formatting
// the order for being sent

TEST_F(OrderManagerTests, fullSubmitOrderOnBinanceTest) {
  getManager().submitOrder(Exchange::BINANCE, Order("BTC", 10, 1, true, true));
}

TEST_F(OrderManagerTests, submitOrderOnBitmexTest) {
  getManager().submitOrder(Exchange::BITMEX, Order("BTC", 10, 1, true, true));
}

TEST_F(OrderManagerTests, submitOrderOnCoinbaseTest) {
  getManager().submitOrder(Exchange::COINBASE, Order("BTC", 10, 1, true, true));
}
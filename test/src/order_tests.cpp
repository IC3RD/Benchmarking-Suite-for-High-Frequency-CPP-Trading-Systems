#include "../../src/dataManager/Order.h"
#include "gtest/gtest.h"

struct OrderTests : public ::testing::Test {
  std::shared_ptr<Order> order;

  Order& getOrder() { return *order; }

  virtual void SetUp() override {
    order = std::make_shared<Order>("BTC", 1, 100, true, true);
  }

  virtual void TearDown() override {}
};

TEST_F(OrderTests, getVolumeTest) { ASSERT_EQ(getOrder().getVolume(), 100); }

TEST_F(OrderTests, getSymbolTest) { ASSERT_EQ(getOrder().getSymbol(), "BTC"); }

TEST_F(OrderTests, getPriceTest) { ASSERT_EQ(getOrder().getPrice(), 1); }

TEST_F(OrderTests, getIsBuyOrderTest) {
  ASSERT_EQ(getOrder().isBuyOrder(), true);
}
#include "../../src/dataManager/OrderDataStore.h"
#include "gtest/gtest.h"

struct OrderDataStoreTests : public ::testing::Test {
  std::shared_ptr<OrderDataStore> orderDataStore;

  OrderDataStore& getOrderDataStore() { return *orderDataStore; }

  virtual void SetUp() override {
    orderDataStore = std::make_shared<OrderDataStore>();
  }

  virtual void TearDown() override {}
};

TEST_F(OrderDataStoreTests, initialiseTest) { ASSERT_TRUE(true); }

TEST_F(OrderDataStoreTests, initiallyEmptyTest) {
  ASSERT_TRUE(getOrderDataStore().isEmpty());
}

TEST_F(OrderDataStoreTests, notEmptyAfterInsertionTest) {
  ASSERT_TRUE(getOrderDataStore().isEmpty());
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::DUMMY, 100, 1);
  getOrderDataStore().addEntry(data);
  ASSERT_FALSE(getOrderDataStore().isEmpty());
}
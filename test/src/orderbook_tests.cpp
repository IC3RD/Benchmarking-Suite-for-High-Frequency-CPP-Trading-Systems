#include "../../src/dataManager/OrderBook.h"
#include "../../src/exchange/Exchange.h"
#include "gtest/gtest.h"

struct OrderBookTests : public ::testing::Test {
  std::shared_ptr<OrderBook> orderBook;

  OrderBook& getOrderBook() { return *orderBook; }

  virtual void SetUp() override {
    orderBook = std::make_shared<OrderBook>(Exchange::DUMMY);
  }

  virtual void TearDown() override {}
};

TEST_F(OrderBookTests, initialiseTest) { ASSERT_TRUE(true); }

TEST_F(OrderBookTests, hasAsksInitiallyFalseTest) {
  ASSERT_FALSE(getOrderBook().hasAsks());
}

TEST_F(OrderBookTests, hasBidsInitiallyFalseTest) {
  ASSERT_FALSE(getOrderBook().hasBids());
}

TEST_F(OrderBookTests, addAskEntryTest) {
  ASSERT_EQ(getOrderBook().getAskAt(0), nullptr);
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_TRUE(getOrderBook().hasAsks());
  ASSERT_FALSE(getOrderBook().hasBids());
  ASSERT_EQ(getOrderBook().getAskAt(0), data);
}

TEST_F(OrderBookTests, addBidEntryTest) {
  ASSERT_EQ(getOrderBook().getBidAt(0), nullptr);
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_TRUE(getOrderBook().hasBids());
  ASSERT_FALSE(getOrderBook().hasAsks());
  ASSERT_EQ(getOrderBook().getBidAt(0), data);
}

TEST_F(OrderBookTests, getExchangeTest) {
  ASSERT_EQ(getOrderBook().getExchange(), Exchange::DUMMY);
}

TEST_F(OrderBookTests, getHighestBidWhenEmptyHandlingTest) {
  ASSERT_FALSE(getOrderBook().hasBids());
  ASSERT_EQ(getOrderBook().getHighestBid(), nullptr);
}

TEST_F(OrderBookTests, getHighestBidTest) {
  ASSERT_FALSE(getOrderBook().hasBids());
  ASSERT_EQ(getOrderBook().getHighestBid(), nullptr);
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_TRUE(getOrderBook().hasBids());
  ASSERT_EQ(getOrderBook().getHighestBid(), data);
  std::shared_ptr<OrderData> data2 =
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::DUMMY, 101, 1);
  getOrderBook().addEntry(data2);
  ASSERT_EQ(getOrderBook().getHighestBid(), data2);
}

TEST_F(OrderBookTests, getLowestAskWhenEmptyHandlingTest) {
  ASSERT_FALSE(getOrderBook().hasAsks());
  ASSERT_EQ(getOrderBook().getLowestAsk(), nullptr);
}

TEST_F(OrderBookTests, getLowestAskTest) {
  ASSERT_FALSE(getOrderBook().hasAsks());
  ASSERT_EQ(getOrderBook().getLowestAsk(), nullptr);
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_TRUE(getOrderBook().hasAsks());
  ASSERT_EQ(getOrderBook().getLowestAsk(), data);
  std::shared_ptr<OrderData> data2 =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::DUMMY, 99, 1);
  getOrderBook().addEntry(data2);
  ASSERT_EQ(getOrderBook().getLowestAsk(), data2);
}

TEST_F(OrderBookTests, getBidStoreTest) {
  ASSERT_EQ(getOrderBook().getBidStore()->isEmpty(),
            std::make_shared<OrderDataStore>()->isEmpty());
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_NE(getOrderBook().getBidStore()->isEmpty(),
            std::make_shared<OrderDataStore>()->isEmpty());
}

TEST_F(OrderBookTests, getAskStoreTest) {
  ASSERT_EQ(getOrderBook().getAskStore()->isEmpty(),
            std::make_shared<OrderDataStore>()->isEmpty());
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::DUMMY, 100, 1);
  getOrderBook().addEntry(data);
  ASSERT_NE(getOrderBook().getAskStore()->isEmpty(),
            std::make_shared<OrderDataStore>()->isEmpty());
}
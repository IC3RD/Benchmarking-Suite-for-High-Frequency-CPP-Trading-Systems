#include "../../src/exchange/Exchange.h"
#include "../../src/orderDataCollectors/fileReaderListener/FileReaderListener.h"
#include "gtest/gtest.h"

struct ListenerTests : public ::testing::Test {
  // test the implementation of the json parsing and populating the orderbook
  // correctly

  std::shared_ptr<OrderBook> orderBook;
  std::shared_ptr<FileReaderListener> listener;

  FileReaderListener& getListener() { return *listener; }

  OrderBook& getOrderBook() { return *orderBook; }

  virtual void SetUp() override {
    orderBook = std::make_shared<OrderBook>(Exchange::DUMMY);
    listener =
        std::make_shared<FileReaderListener>(*orderBook, Exchange::DUMMY, "");
  }

  virtual void TearDown() override {}
};

TEST_F(ListenerTests, initialisedCorrectly) { ASSERT_TRUE(true); }

TEST_F(ListenerTests, jsonDoNothingOnEmptyInput) {
  nlohmann::json json = nlohmann::json::object({});
  getListener().passJSON(json);
  ASSERT_FALSE(getOrderBook().hasAsks());
  ASSERT_FALSE(getOrderBook().hasBids());
}

TEST_F(ListenerTests, jsonDoNothingOnInvalidInput) {
  nlohmann::json json = nlohmann::json::object({{"asks", 21}});
  getListener().passJSON(json);
  ASSERT_FALSE(getOrderBook().hasAsks());
  ASSERT_FALSE(getOrderBook().hasBids());
}

TEST_F(ListenerTests, jsonAddOneAsk) {
  nlohmann::json json =
      nlohmann::json::object({{"ask", {{"price", 2}, {"volume", 1}}}});
  getListener().passJSON(json);
  ASSERT_TRUE(getOrderBook().hasAsks());
  ASSERT_FALSE(getOrderBook().hasBids());
}

TEST_F(ListenerTests, jsonAddOneBid) {
  nlohmann::json json =
      nlohmann::json::object({{"bid", {{"price", 2}, {"volume", 1}}}});
  getListener().passJSON(json);
  ASSERT_TRUE(getOrderBook().hasBids());
  ASSERT_FALSE(getOrderBook().hasAsks());
}

TEST_F(ListenerTests, jsonAddOneBidAndOneAsk) {
  nlohmann::json json =
      nlohmann::json::object({{"ask", {{"price", 2}, {"volume", 1}}},
                              {"bid", {{"price", 2}, {"volume", 1}}}});
  getListener().passJSON(json);
  ASSERT_TRUE(getOrderBook().hasBids());
  ASSERT_TRUE(getOrderBook().hasAsks());
}

TEST_F(ListenerTests, readFromFileDummyTest) {
  getListener().readDataFromFile();
  ASSERT_FALSE(getOrderBook().getAskStore()->isEmpty());
}
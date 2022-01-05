#include "gtest/gtest.h"
#include "tradingStrategies/bollingerBand/BollingerBand.h"

struct BollingerTests : public ::testing::Test {
  std::shared_ptr<BollingerBand> bollingerStrategy;
  std::shared_ptr<OrderBook> orderBook;

  BollingerBand& getBollingerStrategy() { return *bollingerStrategy; }

  OrderBook& getOrderBook() { return *orderBook; }

  virtual void SetUp() override {
    bollingerStrategy = std::make_shared<BollingerBand>();
    orderBook = std::make_shared<OrderBook>(Exchange::BINANCE);
    orderBook->addTradingStrategy(bollingerStrategy);
    bollingerStrategy->addExchange(Exchange::BINANCE);
    bollingerStrategy->insertNewOrderBook(orderBook);
    // tradingStrategy->addExchange(Exchange::BINANCE);
  }

  virtual void TearDown() override {}
};

TEST_F(BollingerTests, initialisationTest) {
  ASSERT_NE(&getBollingerStrategy(), nullptr);
}

TEST_F(BollingerTests, addBitmexExchangeTest) {
  getBollingerStrategy().addExchange(Exchange::BITMEX);
  ASSERT_TRUE(getBollingerStrategy().hasBand());
}

TEST_F(BollingerTests, addNewDataTest) {
  getBollingerStrategy().newData(
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::BINANCE, 100, 1));
  ASSERT_TRUE(
      getOrderBook()
          .getBidStore()
          ->isEmpty());  // since the data was not added via the order book
}

TEST_F(BollingerTests, addDataToOrderBookAlertsTradingStrategyTriggersBuy) {
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::BINANCE, 100, 1));
  ASSERT_FALSE(getOrderBook().getBidStore()->isEmpty());
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 102, 1));
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 95, 1));
}

TEST_F(BollingerTests, addDataToOrderBookAlertsTradingStrategyTriggersSell) {
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::BINANCE, 100, 1));
  ASSERT_FALSE(getOrderBook().getBidStore()->isEmpty());
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 102, 1));
  getOrderBook().addEntry(
      std::make_shared<OrderData>(OrderTypes::BID, Exchange::BINANCE, 105, 1));
}

/*
TEST_F(TradingStrategyTests, buyExecuteTest) {
    getTradingStrategy().buy(std::make_shared<OrderData>(OrderTypes::ASK,
Exchange::BINANCE, 100.0, 1));
}

TEST_F(TradingStrategyTests, sellExecuteTest) {
    getTradingStrategy().sell(std::make_shared<OrderData>(OrderTypes::BID,
Exchange::BINANCE, 100.0, 1));
}


TEST_F(TradingStrategyTests, insertOrderBookTest) {
    getTradingStrategy().insertNewOrderBook(std::make_shared<OrderBook>(Exchange::DUMMY));
}
*/
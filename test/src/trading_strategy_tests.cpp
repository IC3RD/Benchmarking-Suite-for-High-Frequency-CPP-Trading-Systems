#include "gtest/gtest.h"
#include "tradingStrategies/bollingerBand/BollingerBand.h"

struct TradingStrategyTests : public ::testing::Test {
  std::shared_ptr<TradingStrategy> tradingStrategy;

  TradingStrategy& getTradingStrategy() { return *tradingStrategy; }

  virtual void SetUp() override {
    tradingStrategy = std::make_shared<BollingerBand>();
    // tradingStrategy->addExchange(Exchange::BINANCE);
  }

  virtual void TearDown() override {}
};

TEST_F(TradingStrategyTests, initialisationTest) {
  ASSERT_NE(&getTradingStrategy(), nullptr);
}

TEST_F(TradingStrategyTests, buyExecuteTest) {
  getTradingStrategy().buy(std::make_shared<OrderData>(
      OrderTypes::ASK, Exchange::BINANCE, 100.0, 1));
}

TEST_F(TradingStrategyTests, sellExecuteTest) {
  getTradingStrategy().sell(std::make_shared<OrderData>(
      OrderTypes::BID, Exchange::BINANCE, 100.0, 1));
}

TEST_F(TradingStrategyTests, insertOrderBookTest) {
  getTradingStrategy().insertNewOrderBook(
      std::make_shared<OrderBook>(Exchange::DUMMY));
  ASSERT_TRUE(getTradingStrategy().hasOrderBook());
}

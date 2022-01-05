#include <string>

#include "gtest/gtest.h"
#include "ordering-system/OrderManager.h"

struct OrderExecutorTests : public ::testing::Test {
  std::shared_ptr<BinanceOrderExecutor> binanceExecutor;
  std::shared_ptr<BitmexOrderExecutor> bitmexExecutor;
  std::shared_ptr<CoinbaseOrderExecutor> coinbaseExecutor;

  BinanceOrderExecutor& getBinanceExecutor() { return *binanceExecutor; }

  BitmexOrderExecutor& getBitmexExecutor() { return *bitmexExecutor; }

  CoinbaseOrderExecutor& getCoinbaseExecutor() { return *coinbaseExecutor; }

  virtual void SetUp() override {
    binanceExecutor = std::make_shared<BinanceOrderExecutor>();
    bitmexExecutor = std::make_shared<BitmexOrderExecutor>();
    coinbaseExecutor = std::make_shared<CoinbaseOrderExecutor>();
  }

  virtual void TearDown() override {}
};

TEST_F(OrderExecutorTests, binanceGetDestinationTest) {
  ASSERT_EQ(getBinanceExecutor().getDestination(),
            "https://testnet.binance.vision/api/v3/order?");
}

TEST_F(OrderExecutorTests, binanceGetExchangeNameTest) {
  ASSERT_EQ(getBinanceExecutor().getExchangeName(), "Binance");
}

TEST_F(OrderExecutorTests, binanceParseOrderTest) {
  std::string expected =
      "symbol=BTCUSDT&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=1";
  ASSERT_EQ(getBinanceExecutor()
                .parseOrder(Order("BTC", 100, 1, true, true))
                .substr(0, 69),
            expected);
  // sub string to ignore timestamp data
}

TEST_F(OrderExecutorTests, bitmexGetDestinationTest) {
  ASSERT_EQ(getBitmexExecutor().getDestination(),
            "https://testnet.bitmex.com/api/v1/order");
}

TEST_F(OrderExecutorTests, bitmexGetExchangeNameTest) {
  ASSERT_EQ(getBitmexExecutor().getExchangeName(), "BitMEX");
}

TEST_F(OrderExecutorTests, bitmexParseOrderTest) {
  std::string expected =
      "symbol=XBTUSD&side=Buy&orderQty=1&price=100&ordType=Limit";
  ASSERT_EQ(getBitmexExecutor().parseOrder(Order("BTC", 100, 1, true, true)),
            expected);
}

TEST_F(OrderExecutorTests, coinbaseGetDestinationTest) {
  ASSERT_EQ(getCoinbaseExecutor().getDestination(),
            "https://api-public.sandbox.pro.coinbase.com/orders");
}

TEST_F(OrderExecutorTests, coinbaseGetExchangeNameTest) {
  ASSERT_EQ(getCoinbaseExecutor().getExchangeName(), "Coinbase");
}

TEST_F(OrderExecutorTests, coinbaseParseOrderTest) {
  std::string expected =
      "{\"price\":\"1\",\"product_id\":\"BTC-USD\",\"side\":\"buy\",\"size\":"
      "\"1\"}";
  ASSERT_EQ(getCoinbaseExecutor().parseOrder(Order("BTC", 100, 1, true, true)),
            expected);
}

/*
TEST_F(OrderExecutorTests, actualOrderSendToTestCurl) {
    getCoinbaseExecutor().submitOrder(Order("BTC", 100, 1, true, false));
}
*/

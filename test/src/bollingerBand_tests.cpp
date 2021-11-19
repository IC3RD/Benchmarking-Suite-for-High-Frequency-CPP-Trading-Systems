#include <gtest/gtest.h>

#include "../../src/bollingerBand/BollingerBand.h"
#include "../../src/exchange/Exchange.h"

struct BollingerBandTests : public ::testing::Test {
  BollingerBand* band;

  BollingerBand& getTestBand() { return *band; }

  virtual void SetUp() override { band = new BollingerBand(100); }

  virtual void TearDown() override { delete band; }
};

/*

TEST_F(BollingerBandTests, correctMeanCalculatedInitially) {
  MarketData data = MarketData("Example", 6, 4, 100, Exchange::BITMEX);
  getTestBand().strategy(&data);
  ASSERT_EQ(getTestBand().getCurrMovingAverage(), 5);
}

TEST_F(BollingerBandTests, correctMeanCalculatedAfter10Inputs) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2 + i, i, 100, Exchange::BITMEX);
    getTestBand().strategy(&data);
  }
  ASSERT_EQ(getTestBand().getCurrMovingAverage(), 5.5);
}

TEST_F(BollingerBandTests, stdDeviationOfSamePricesIsZero) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2, 1, 100, Exchange::BITMEX);
    getTestBand().strategy(&data);
    ASSERT_EQ(getTestBand().getCurrStdDeviation(), 0.0);
  }
}

TEST_F(BollingerBandTests, stdDeviationCorrectAfter10Inputs) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2 + i, i, 100, Exchange::BITMEX);
    getTestBand().strategy(&data);
  }
  ASSERT_TRUE(getTestBand().getCurrStdDeviation() >= 3.027 &&
              getTestBand().getCurrStdDeviation() <= 3.029);
}

*/

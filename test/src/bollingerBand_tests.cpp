#include <gtest/gtest.h>
#include "../../src/bollingerBand/BollingerBand.h"
#include "../../src/bollingerBand/MarketData.h"

struct BollingerBandTests : public :: testing::Test {
  
  BollingerBand* band;
  
  BollingerBand getTestBand() {
    return *band;
  }
  
  virtual void SetUp() override {
    cout << "Setting up bollinger band unit test \n";    
    band = new BollingerBand(100);
  }

  virtual void TearDown() override {
    cout << "Tearing down bollinger band unit test \n";    
    delete band;
  }
};

TEST_F(BollingerBandTests, correctMeanCalculatedInitially) {  
  cout << "start";  
  MarketData *data = new MarketData("Example", 6, 4, 100);
  cout << "initialised";
  getTestBand().strategy(data);
  cout << "yeah";
  ASSERT_EQ(getTestBand().getCurrMovingAverage(), 5);
  delete data;
}

TEST_F(BollingerBandTests, correctMeanCalculatedAfter10Inputs) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2 + i, i, 100);
    getTestBand().strategy(&data);
  }
  ASSERT_EQ(getTestBand().getCurrMovingAverage(), 5.5);
}

TEST_F(BollingerBandTests, stdDeviationOfSamePricesIsZero) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2, 1, 100);
    getTestBand().strategy(&data);
    ASSERT_EQ(getTestBand().getCurrStdDeviation(), 0.0);
  }
}

TEST_F(BollingerBandTests, stdDeviationCorrectAfter10Inputs) {
  for (int i = 0; i < 10; i++) {
    MarketData data = MarketData("Example", 2 + i, i, 100);
    getTestBand().strategy(&data); 
  }
  ASSERT_TRUE(getTestBand().getCurrStdDeviation() >= 3.027 && getTestBand().getCurrStdDeviation() <= 3.029);
}

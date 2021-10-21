#include <gtest/gtest.h>
#include "../../src/bollingerBand/BollingerBand.h"
#include "../../src/bollingerBand/MarketData.h"

struct MarketDataTests : public :: testing::Test {
  
  MarketData* marketData;

  MarketData& getData() {
    return *marketData;
  }  

  virtual void SetUp() override {
    marketData = new MarketData("Example", 7, 3, 100);
  }

  virtual void TearDown() override {
    delete marketData;
  }
};

TEST_F(MarketDataTests, correctInitialisation) {    
  ASSERT_EQ(getData().getPrice(), 5);
  ASSERT_EQ(getData().getVolume(), 100); 
}

TEST_F(MarketDataTests, updateWorksCorrectly) {
  int newVol = 99;
  getData().updateVolume(newVol);
  ASSERT_EQ(getData().getVolume(), newVol);

  int newSell = 5;
  getData().updateSell(newSell);
  ASSERT_EQ(getData().getPrice(), 6);
}




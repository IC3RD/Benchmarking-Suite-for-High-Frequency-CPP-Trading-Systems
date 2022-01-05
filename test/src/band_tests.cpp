#include <math.h>
#include <stdio.h>

#include <numeric>
#include <vector>

#include "../../src/dataManager/OrderBook.h"
#include "../../src/exchange/Exchange.h"
#include "../../src/tradingStrategies/bollingerBand/Band.h"
#include "gtest/gtest.h"

struct BandTests : public ::testing::Test {
  Band* band;
  std::shared_ptr<OrderBook> orderBook;

  Band& getBand() { return *band; }

  std::shared_ptr<OrderBook> getOrderBook() { return orderBook; }

  virtual void SetUp() override {
    band = new Band();
    orderBook = std::make_shared<OrderBook>(Exchange::DUMMY);
  }

  virtual void TearDown() override { delete band; }
};

TEST_F(BandTests, initialseTest) { ASSERT_TRUE(true); }

TEST_F(BandTests, meanInitaillyZeroTest) { ASSERT_EQ(getBand().getMean(), 0); }

TEST_F(BandTests, stdDevInitiallyZeroTest) { ASSERT_EQ(getBand().getStd(), 0); }

TEST_F(BandTests, noOfElementsInitiallyZeroTest) {
  ASSERT_EQ(getBand().getNoOfElements(), 0);
}

TEST_F(BandTests, meanBecomesElementAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value, getOrderBook());
  ASSERT_EQ(getBand().getMean(), value);
}

TEST_F(BandTests, elementsBecomesOneAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value, getOrderBook());
  ASSERT_EQ(getBand().getNoOfElements(), 1);
}

TEST_F(BandTests, stdDevIsZeroAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value, getOrderBook());
  ASSERT_EQ(getBand().getStd(), 0);
}

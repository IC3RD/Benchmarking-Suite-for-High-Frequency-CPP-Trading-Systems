#pragma once

#include "gtest/gtest.h"
#include "../../src/tradingStrategies/bollingerBand/Band.h"

#include <vector>
#include <numeric>
#include <stdio.h>
#include <math.h>


struct BandTests : public ::testing::Test {    
  Band *band;

    Band& getBand() {
        return *band;
    }

  virtual void SetUp() override {
      band = new Band();
  }

  virtual void TearDown() override { delete band; }
};

TEST_F(BandTests, initialseTest) {
  ASSERT_TRUE(true);
}

TEST_F(BandTests, meanInitaillyZeroTest) {
  ASSERT_EQ(getBand().getMean(), 0);
}

TEST_F(BandTests, stdDevInitiallyZeroTest) {
  ASSERT_EQ(getBand().getStd(), 0);
}

TEST_F(BandTests, noOfElementsInitiallyZeroTest) {
  ASSERT_EQ(getBand().getNoOfElements(), 0);
}

TEST_F(BandTests, meanBecomesElementAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value);
  ASSERT_EQ(getBand().getMean(), value);
}

TEST_F(BandTests, elementsBecomesOneAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value);
  ASSERT_EQ(getBand().getNoOfElements(), 1);
}

TEST_F(BandTests, stdDevIsZeroAfterSingleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value);
  ASSERT_EQ(getBand().getStd(), 0);
}

TEST_F(BandTests, meanUpdatesCorrectlyAfterMultipleInsertionTest) {
  long value = 1;
  getBand().insertNewData(value);
  ASSERT_EQ(getBand().getMean(), value);
  getBand().insertNewData(3);
  ASSERT_EQ(getBand().getMean(), 2);
}
/*
TEST_F(BandTests, stdDevUpdatesCorrectlyAfterMultipleInsertionTest) {
  ASSERT_EQ(getBand().getStd(), 0);
  getBand().insertNewData(1);
  ASSERT_EQ(getBand().getStd(), 0);
  getBand().insertNewData(3);
  ASSERT_EQ(getBand().getMean(), 2);
  ASSERT_EQ(sqrt(2), getBand().getStd());
  getBand().insertNewData(5);
  ASSERT_EQ(sqrt(2), getBand().getStd());
}
*/
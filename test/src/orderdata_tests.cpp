#pragma once

#include "gtest/gtest.h"
#include "../../src/dataManager/OrderData.h"
#include "../../src/dataManager/OrderTypes.h"
#include "../../src/exchange/Exchange.h"

struct OrderDataTests : public ::testing::Test {
    OrderData *orderData;

    OrderData& getOrderData() {
        return *orderData;
    }

  virtual void SetUp() override {
      orderData = new OrderData(OrderTypes::ASK, Exchange::BINANCE, 100, 1);
  }

  virtual void TearDown() override { delete orderData; }
};

TEST_F(OrderDataTests, initialiseCorrectly) { ASSERT_TRUE(true); }

TEST_F(OrderDataTests, getOrderType) { ASSERT_EQ(getOrderData().getOrderType(), OrderTypes::ASK); }

TEST_F(OrderDataTests, getExchange) { ASSERT_EQ(getOrderData().getExchange(), Exchange::BINANCE); }

TEST_F(OrderDataTests, getOrderPrice) { ASSERT_EQ(getOrderData().getOrderPrice(), 100); }

TEST_F(OrderDataTests, getOrderVolume) { ASSERT_EQ(getOrderData().getOrderVolume(), 1); }
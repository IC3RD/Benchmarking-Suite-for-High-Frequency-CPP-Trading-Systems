#include "stdio.h"
#include "gtest/gtest.h"

struct ExampleTests : public :: testing::Test {

  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
};

TEST_F(ExampleTests, AutoPass1) {
  ASSERT_TRUE(true);
}

TEST_F(ExampleTests, AutoPass2) {
  ASSERT_TRUE(true);
}

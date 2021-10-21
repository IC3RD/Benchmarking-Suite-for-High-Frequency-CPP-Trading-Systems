#include "stdio.h"
#include "gtest/gtest.h"

struct ExampleTests : public :: testing::Test {

  virtual void SetUp() override {
    std::cout << "Setting up example unit test \n";    
  }

  virtual void TearDown() override {
    std::cout << "Tearing down example unit test \n";    
  }
};

TEST_F(ExampleTests, AutoPass1) {
  ASSERT_TRUE(true);
}

TEST_F(ExampleTests, AutoPass2) {
  ASSERT_TRUE(true);
}

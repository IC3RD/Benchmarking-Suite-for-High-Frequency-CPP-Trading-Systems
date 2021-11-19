#pragma once

#include <memory>

#include "exchange/OrderData.h"

class Band {
 public:
  Band();
  ~Band();
  long getMean();
  long getStd();
  int getNoOfElements();
  void insertNewData(long);

 private:
  long meanPrice;
  long stdDeviation;
  int noOfElements;
};

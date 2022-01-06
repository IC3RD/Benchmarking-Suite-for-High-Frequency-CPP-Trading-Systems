#pragma once

#include <memory>

#include "dataManager/OrderBook.h"
#include "dataManager/OrderData.h"

class Band {
 public:
  Band();
  ~Band();
  long long getMean();
  long long getStd();
  int getNoOfElements();
  void insertNewData(long, std::shared_ptr<OrderBook>);

 private:
  long long meanPrice;
  long long stdDeviation;
  int noOfElements;
};

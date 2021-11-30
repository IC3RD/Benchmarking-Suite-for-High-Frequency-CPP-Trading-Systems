#pragma once

#include <memory>

#include "dataManager/OrderBook.h"
#include "dataManager/OrderData.h"

class Band {
 public:
  Band();
  ~Band();
  long getMean();
  long getStd();
  int getNoOfElements();
  void insertNewData(long, std::shared_ptr<OrderBook>);

 private:
  long meanPrice;
  long stdDeviation;
  int noOfElements;
};

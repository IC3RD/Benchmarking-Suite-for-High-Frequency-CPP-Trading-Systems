#pragma once

#include <memory>

#include "dataManager/OrderData.h"
#include "dataManager/OrderBook.h"


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

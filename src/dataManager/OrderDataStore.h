#pragma once
#include <map>
#include <memory>
#include <mutex>

#include "dataManager/OrderData.h"

class OrderDataStore {
 public:
  OrderDataStore();
  void addEntry(std::shared_ptr<OrderData>);
  bool isEmpty();
  std::map<long, std::shared_ptr<OrderData>> getPriceToOrderDataMap();

 private:
  std::map<long, std::shared_ptr<OrderData>> priceToOrderDataMap;
  std::mutex mutex_dataHistory;
};

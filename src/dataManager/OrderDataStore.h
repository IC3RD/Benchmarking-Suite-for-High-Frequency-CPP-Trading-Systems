#pragma once
#include <memory>
#include <mutex>
#include <vector>

#include "concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "exchange/OrderData.h"

class OrderDataStore {
public:
  OrderDataStore();
  void addEntry(OrderData);
  void sendOrder();
private:
  std::size_t storeIdx;
  std::size_t nextIdx;
  std::vector<OrderData> dataHistory;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
};
#pragma once
#include <map>
#include <memory>
#include <mutex>

#include "concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "exchange/OrderData.h"

class OrderDataStore {
 public:
  OrderDataStore();
  void addEntry(std::shared_ptr<OrderData>);
  void sendOrder();
  void updateBest(long);
  long getBest();
  std::shared_ptr<OrderData> getEntry(long);

 private:
  std::size_t storeIdx;
  std::size_t nextIdx;
  std::map<long, std::shared_ptr<OrderData>> dataHistory;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
  long best;
};
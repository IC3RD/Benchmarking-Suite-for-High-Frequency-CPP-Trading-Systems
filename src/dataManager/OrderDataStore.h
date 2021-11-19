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
  bool isEmpty();
  std::shared_ptr<OrderData> getFirst();
  std::shared_ptr<OrderData> getLast();
  std::map<long, std::shared_ptr<OrderData>> getPriceToOrderDataMap();

 private:
  std::size_t storeIdx;
  std::size_t nextIdx;
  std::map<long, std::shared_ptr<OrderData>> priceToOrderDataMap;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
};
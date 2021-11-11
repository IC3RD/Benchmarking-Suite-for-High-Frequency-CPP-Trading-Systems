#pragma once
#include <deque>
#include <memory>
#include <mutex>
#include <vector>
#include <memory>

#include "concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "exchange/OrderData.h"
#include "exchange/OrderTypes.h"
#include "exchange/TradingStrategy.h"
#include "dataManager/OrderDataStore.h"

class OrderBook {
 public:
  OrderBook();
  ~OrderBook();
  // void addTradingStrategy(TradingStrategy&);
  void addEntry(std::shared_ptr<OrderData>);
  void sendOrder();
  OrderDataStore getBidStore();
  OrderDataStore getAskStore();

 private:
  std::deque<std::unique_ptr<TradingStrategy>> listenerStrategies;
  std::unique_ptr<OrderDataStore> bidStore;
  std::unique_ptr<OrderDataStore> askStore;
};
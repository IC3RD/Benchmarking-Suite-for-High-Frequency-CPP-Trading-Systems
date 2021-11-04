#pragma once
#include <mutex>
#include <deque>

#include "../exchange/MarketData.h"
#include "../exchange/TradingStrategy.h"
#include "ConcurrentUnorderedSet/CoarseGrainedUnorderedSet.h"

class DataManager {
 public:
  DataManager();
  ~DataManager();
  void addTradingStrategy(TradingStrategy&);
  void addEntry(MarketData&);
  void sendOrder();
  MarketData& getMostRecentMarketData();
 private:
  std::size_t storeIdx = -1;
  std::size_t nextIdx = 0;
  std::vector<MarketData*> dataHistory;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
  std::deque<TradingStrategy*> *listenerStrategies;
};
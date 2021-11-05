#pragma once
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

#include "../bollingerBand/BollingerBand.h"
#include "../concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "../exchange/MarketData.h"
#include "../exchange/TradingStrategy.h"

class DataManager {
 public:
  DataManager();
  // void addTradingStrategy(TradingStrategy&);
  void addEntry(MarketData);
  void sendOrder();
  MarketData& getMostRecentMarketData();

 private:
  std::size_t storeIdx;
  std::size_t nextIdx;
  std::vector<MarketData> dataHistory;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
  std::deque<std::unique_ptr<TradingStrategy>> listenerStrategies;
};
#pragma once
#include <deque>
#include <mutex>
#include <vector>
#include <memory>

#include "../exchange/MarketData.h"
#include "../exchange/TradingStrategy.h"
#include "../bollingerBand/BollingerBand.h"
#include "../concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"

class DataManager {
 public:
  DataManager();
  //void addTradingStrategy(TradingStrategy&);
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
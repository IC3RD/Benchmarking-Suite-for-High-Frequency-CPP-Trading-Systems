#pragma once
#include <mutex>
#include <vector>

#include "AssetData.h"
#include "ConcurrentUnorderedSet/CoarseGrainedUnorderedSet.h"

class DataManager {
 public:
  void addEntry(AssetData);
  void sendOrder();

 private:
  std::size_t storeIdx = -1;
  std::size_t nextIdx = 0;
  std::vector<AssetData> dataHistory;
  std::mutex mutex_dataHistory;
  CoarseGrainedUnorderedSet<std::size_t> set;
};

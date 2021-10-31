#include "DataManager.h"

#include <iostream>

#include "AssetData.h"

void DataManager::addEntry(AssetData assetData) {
  mutex_dataHistory.lock();
  int i = ++storeIdx;
  if (i >= dataHistory.size()) {
    dataHistory.resize((i + 1) * 2);
  }
  mutex_dataHistory.unlock();
  std::cout << "index where the data should be stored is " << i << std::endl;
  dataHistory[i] = assetData;
  set.insert(i);
}

void DataManager::sendOrder() {
  // keep on spinning the thread to check if a new order can be sent
  while (true) {
    set.lock();
    while (set.contains(nextIdx)) {
      // process and send order if necessary
      std::cout << "The asset being processed is " << nextIdx << std::endl;

      set.erase(nextIdx++);
    }
    set.unlock();
  }
}

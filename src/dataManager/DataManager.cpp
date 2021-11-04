#include "DataManager.h"

#include <iostream>

DataManager::DataManager() {
  listenerStrategies = new std::deque<TradingStrategy*>();
  storeIdx = -1;
  nextIdx = 0;
}

DataManager::~DataManager() { delete listenerStrategies; }

void DataManager::addTradingStrategy(TradingStrategy& strategy) {
  listenerStrategies->push_back(&strategy);
}

void DataManager::addEntry(MarketData& marketData) {
  mutex_dataHistory.lock();
  int i = ++storeIdx;
  mutex_dataHistory.unlock();
  std::cout << "index where the data should be stored is " << i << std::endl;
  // each thread has it's own value of i which is correct relative to the
  // concurrent value storeindex
  dataHistory[i] = &marketData;
  set.insert(i);
  for (auto it = listenerStrategies->cbegin(); it != listenerStrategies->cend(); it = std::next(it, 1)) {
    (*it)->updateData(marketData);
  }
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

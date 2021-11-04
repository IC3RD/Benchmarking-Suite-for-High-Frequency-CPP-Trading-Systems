#include "DataManager.h"
#include "../bollingerBand/BollingerBand.h"
#include "../arbitrage/Arbitrage.h"

#include <iostream>

DataManager::DataManager() {
  listenerStrategies = new std::deque<TradingStrategy*>(1000);
  listenerStrategies->push_back(new BollingerBand(100));
  //listenerStrategies->push_back(new Arbitrage());
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
  if (i >= dataHistory.size()) {
    dataHistory.resize((i+1)*2);
  }
  mutex_dataHistory.unlock();
  std::cout << "index where the data should be stored is " << i << std::endl;
  // each thread has it's own value of i which is correct relative to the
  // concurrent value storeindex
  dataHistory[i] = &marketData;
  set.insert(i);
  for (auto it = listenerStrategies->cbegin(); it != listenerStrategies->cend(); ++it) {
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

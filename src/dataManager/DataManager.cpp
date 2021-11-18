#include "DataManager.h"

#include <iostream>
#include <memory>

#include "../arbitrage/Arbitrage.h"
#include "../bollingerBand/BollingerBand.h"

DataManager::DataManager() {
  listenerStrategies.push_back(std::make_unique<BollingerBand>(100));
  // listenerStrategies->push_back(new Arbitrage());
  nextIdx = 0;
}

// void DataManager::addTradingStrategy(TradingStrategy &strategy) {
//  listenerStrategies.push_back(strategy);
//}

void DataManager::addEntry(MarketData marketData) {
  mutex_dataHistory.lock();
  dataHistory.push_back(marketData);
  int i = dataHistory.size() - 1;

  mutex_dataHistory.unlock();
  std::cout << "index where the data should be stored is " << i << std::endl;
  // each thread has it's own value of i which is correct relative to the
  // concurrent value storeindex
  // set.insert(i); TODO
  for (auto it = listenerStrategies.begin(); it != listenerStrategies.end();
       ++it) {
    (*it)->updateData(marketData);
  }
}

void DataManager::sendOrder() {
  // keep on spinning the thread to check if a new order can be sent
  std::cout << "Spinning: " << std::this_thread::get_id() << std::endl;
  while (true) {
    set.lock();
    while (set.contains(nextIdx)) {
      // process and send order if necessary
      std::cout << "The asset being processed is " << nextIdx << std::endl;
      nextIdx++;
      // set.erase(nextIdx++);
    }
    set.unlock();
  }
}

#include "OrderDataStore.h"

OrderDataStore::OrderDataStore() {
    nextIdx = 0;
    best = 0;
}

void OrderDataStore::updateBest(long newBest) {
  best = newBest;
}

long OrderDataStore::getBest() {
  return best;
}

void OrderDataStore::addEntry(std::shared_ptr<OrderData> orderData) {
  mutex_dataHistory.lock();
  std::map<long, std::shared_ptr<OrderData>>::iterator it = dataHistory.find(orderData->getOrderPrice());
  if (it != dataHistory.end()) { // if this key already in map
    if (orderData->getOrderVolume() == 0) {
      dataHistory.erase(orderData->getOrderPrice());
    } else {
      it->second = orderData;
    }
  } else {
    dataHistory.insert(std::make_pair(orderData->getOrderPrice(), orderData));
  }
  int i = dataHistory.size() - 1;
  mutex_dataHistory.unlock();
  //std::cout << "index where the data should be stored is " << i << std::endl;
}

void OrderDataStore::sendOrder() {
  while (true) {
    set.lock();
    while (set.contains(nextIdx)) {
      // process and send order if necessary
      //std::cout << "The asset being processed is " << nextIdx << std::endl;
      nextIdx++;
      // set.erase(nextIdx++);
    }
    set.unlock();
  }
}
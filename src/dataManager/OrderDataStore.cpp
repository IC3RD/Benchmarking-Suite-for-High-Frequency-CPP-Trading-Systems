#include "OrderDataStore.h"

OrderDataStore::OrderDataStore() {
    nextIdx = 0;
}

void OrderDataStore::addEntry(std::shared_ptr<OrderData> orderData) {
  mutex_dataHistory.lock();
  dataHistory.insert(std::make_pair(orderData->getOrderPrice(), orderData));
  int i = dataHistory.size() - 1;
  mutex_dataHistory.unlock();
  //std::cout << "index where the data should be stored is " << i << std::endl;
}

OrderData OrderDataStore::getEntry(int i){
  return *(dataHistory.find(dataHistory.size() - i - 1));
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
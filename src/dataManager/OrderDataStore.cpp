#include "OrderDataStore.h"

OrderDataStore::OrderDataStore() { nextIdx = 0; }

std::map<long, std::shared_ptr<OrderData>>
OrderDataStore::getPriceToOrderDataMap() {
  return priceToOrderDataMap;
}

void OrderDataStore::addEntry(std::shared_ptr<OrderData> orderData) {
  mutex_dataHistory.lock();
  std::map<long, std::shared_ptr<OrderData>>::iterator it =
      priceToOrderDataMap.find(orderData->getOrderPrice());
  if (it != priceToOrderDataMap.end()) {  // if this key already in map
    if (orderData->getOrderVolume() == 0) {
      priceToOrderDataMap.erase(orderData->getOrderPrice());
    } else {
      it->second = orderData;
    }
  } else {
    priceToOrderDataMap.insert(
        std::make_pair(orderData->getOrderPrice(), orderData));
  }
  int i = priceToOrderDataMap.size() - 1;
  mutex_dataHistory.unlock();
  // std::cout << "index where the data should be stored is " << i << std::endl;
}

void OrderDataStore::sendOrder() {
  while (true) {
    set.lock();
    while (set.contains(nextIdx)) {
      // process and send order if necessary
      // std::cout << "The asset being processed is " << nextIdx << std::endl;
      nextIdx++;
      // set.erase(nextIdx++);
    }
    set.unlock();
  }
}

bool OrderDataStore::isEmpty() { return priceToOrderDataMap.empty(); }

std::shared_ptr<OrderData> OrderDataStore::getLast(){
    mutex_dataHistory.lock();
    std::shared_ptr<OrderData> res = std::prev(priceToOrderDataMap.end())
                                       ->second;
    mutex_dataHistory.unlock();
    return res;
}

std::shared_ptr<OrderData> OrderDataStore::getFirst() {
  mutex_dataHistory.lock();
  std::shared_ptr<OrderData> res = priceToOrderDataMap.begin()->second;
  mutex_dataHistory.unlock();
  return res;
}

#include "OrderDataStore.h"

OrderDataStore::OrderDataStore() {}

std::map<long, std::shared_ptr<OrderData>>
OrderDataStore::getPriceToOrderDataMap() {
  return priceToOrderDataMap;
}

std::shared_ptr<OrderData> OrderDataStore::getLast() {
  mutex_dataHistory.lock();
  std::shared_ptr<OrderData> res = std::prev(priceToOrderDataMap.end())->second;
  mutex_dataHistory.unlock();
  return res;
}

std::shared_ptr<OrderData> OrderDataStore::getFirst() {
  mutex_dataHistory.lock();
  std::shared_ptr<OrderData> res = priceToOrderDataMap.begin()->second;
  mutex_dataHistory.unlock();
  return res;
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
  mutex_dataHistory.unlock();
}

bool OrderDataStore::isEmpty() { return priceToOrderDataMap.empty(); }

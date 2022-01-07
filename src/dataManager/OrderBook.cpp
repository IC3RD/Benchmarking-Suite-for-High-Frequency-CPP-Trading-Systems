
#include "OrderBook.h"

OrderBook::OrderBook(Exchange::ExchangeName exchange)
    : exchange(exchange),
      bidStore(std::make_shared<OrderDataStore>()),
      askStore(std::make_shared<OrderDataStore>()),
      stores({askStore, bidStore}) {}

OrderBook::~OrderBook() {}

void OrderBook::addTradingStrategy(
    std::shared_ptr<TradingStrategy> tradingStrategy) {
  listenerStrategies.push_back(tradingStrategy);
}

void OrderBook::addEntry(std::shared_ptr<OrderData> data) {
  stores[data->getOrderType()]->addEntry(data);
  for (auto it = listenerStrategies.begin(); it != listenerStrategies.end();
       ++it) {
#ifndef ENABLE_CPP_BENCHMARKS
    (*it)->newData(data);
#endif
  }
}

const Exchange::ExchangeName OrderBook::getExchange() const { return exchange; }

std::shared_ptr<OrderData> OrderBook::getHighestBid() {
  if (bidStore->isEmpty()) {
    return nullptr;
  }
  return (--(bidStore->getPriceToOrderDataMap().end()))->second;
}

std::shared_ptr<OrderData> OrderBook::getLowestAsk() {
  if (askStore->isEmpty()) {
    return nullptr;
  }
  return askStore->getPriceToOrderDataMap().begin()->second;
}

std::shared_ptr<OrderData> OrderBook::getBidAt(int i) {
  if (bidStore->isEmpty() || i < 0) {
    return nullptr;
  }
  auto it = --(bidStore->getPriceToOrderDataMap().end());
  while (i > 0) {
    it--;
    --i;
  }
  return it->second;
}
std::shared_ptr<OrderData> OrderBook::getAskAt(int i) {
  if (askStore->isEmpty() || i < 0) {
    return nullptr;
  }
  auto it = (askStore->getPriceToOrderDataMap().begin());
  while (i > 0) {
    it++;
    --i;
  };
  return it->second;
}

std::shared_ptr<OrderDataStore> OrderBook::getBidStore() { return bidStore; }

std::shared_ptr<OrderDataStore> OrderBook::getAskStore() { return askStore; }

bool OrderBook::hasAsks() { return !askStore->isEmpty(); }

bool OrderBook::hasBids() { return !bidStore->isEmpty(); }

#pragma once
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

#include "concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "dataManager/OrderDataStore.h"
#include "exchange/Exchange.h"
#include "exchange/OrderData.h"
#include "exchange/OrderTypes.h"
#include "exchange/TradingStrategy.h"

class TradingStrategy;

class OrderBook {
 public:
  OrderBook(Exchange::ExchangeName);
  ~OrderBook();
  void addTradingStrategy(std::shared_ptr<TradingStrategy>);
  void addEntry(std::shared_ptr<OrderData>);
  void sendOrder();
  const Exchange::ExchangeName getExchange() const;
  std::shared_ptr<OrderDataStore> getBidStore();
  std::shared_ptr<OrderDataStore> getAskStore();

 private:
  std::deque<std::shared_ptr<TradingStrategy>> listenerStrategies;
  std::shared_ptr<OrderDataStore> bidStore;
  std::shared_ptr<OrderDataStore> askStore;
  const Exchange::ExchangeName exchange;
};
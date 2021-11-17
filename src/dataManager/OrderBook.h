#pragma once
#include <deque>
#include <memory>
#include <mutex>
#include <vector>
#include <memory>

#include "concurrentUnorderedSet/CoarseGrainedUnorderedSet.h"
#include "exchange/OrderData.h"
#include "exchange/OrderTypes.h"
#include "exchange/Exchange.h"
#include "exchange/TradingStrategy.h"
#include "dataManager/OrderDataStore.h"

class OrderBook {
 public:
  OrderBook(Exchange::ExchangeName);
  ~OrderBook();
  void addTradingStrategy(std::shared_ptr<TradingStrategy>);
  void addEntry(std::shared_ptr<OrderData>);
  void sendOrder();
  const Exchange::ExchangeName getExchange() const;

 private:
  std::deque<std::shared_ptr<TradingStrategy>> listenerStrategies;
  std::unique_ptr<OrderDataStore> bidStore;
  std::unique_ptr<OrderDataStore> askStore;
  const Exchange::ExchangeName exchange;
};
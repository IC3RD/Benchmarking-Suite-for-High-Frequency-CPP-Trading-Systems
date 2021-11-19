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
#include "tradingStrategies/TradingStrategy.h"

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
  std::shared_ptr<OrderData> getHighestBid();
  std::shared_ptr<OrderData> getLowestAsk();
  std::shared_ptr<OrderData> getBidAt(int i);
  std::shared_ptr<OrderData> getAskAt(int i);

 private:
  std::deque<std::shared_ptr<TradingStrategy>> listenerStrategies;
  std::shared_ptr<OrderDataStore> bidStore;
  std::shared_ptr<OrderDataStore> askStore;
  const Exchange::ExchangeName exchange;
};
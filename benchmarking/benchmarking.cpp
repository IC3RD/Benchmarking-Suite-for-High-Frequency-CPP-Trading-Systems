#include <benchmark/benchmark.h>
#include "bollingerBand/BollingerBand.h"
#include "dataManager/OrderDataStore.h"
#include "exchange/Exchange.h"
#include "dataManager/OrderData.h"
#include "dataManager/OrderTypes.h"
#include "tradingStrategies/TradingStrategy.h"
#include "ordering-system/exchangeExecutors/bitmex/BitmexOrderExecutor.h"
#include <memory>

// Define another benchmark
static void BM_OrderExecutor_submitOrder(benchmark::State &state) {
  Order order{"XBTUSD", 100, 5, true};
  BinanceOrderExecutor executor{};
  executor.enableBenchmarking();
  //    executor.enableOutput();
  for (auto _ : state) {
    executor.submitOrder(order);
  }
}

BENCHMARK(BM_OrderExecutor_submitOrder);

// Define another benchmark
static void BM_OrderBook_getHighestBid(benchmark::State &state) {
  OrderBook book{Exchange::BITMEX};
  for (auto _ : state) {
    book.getHighestBid();
  }
}

BENCHMARK(BM_OrderBook_getHighestBid);

// Define another benchmark
static void BM_OrderBook_getLowestAsk(benchmark::State &state) {
  OrderBook book{Exchange::BITMEX};
  for (auto _ : state) {
    book.getLowestAsk();
  }
}

BENCHMARK(BM_OrderBook_getLowestAsk);

// Define another benchmark
static void BM_OrderDataStore_addEntry(benchmark::State &state) {
  // OrderTypes::OrderType type, Exchange::ExchangeName name, long price,
  //            double volume
  //    OrderData test_data {OrderTypes::ASK, Exchange::BITMEX, 500, 100};
  std::shared_ptr ptr =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 500, 100);
  OrderDataStore dataStore{};
  for (auto _ : state) {
    dataStore.addEntry(ptr);
  }
}

BENCHMARK(BM_OrderDataStore_addEntry);

// OrderDataStore but path where key already exists...but volume != 0
static void BM_OrderDataStore_addEntry_keyAlreadyExists(
    benchmark::State &state) {
  std::shared_ptr ptr =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 500, 100);
  OrderDataStore dataStore{};
  dataStore.addEntry(ptr);
  for (auto _ : state) {
    dataStore.addEntry(ptr);
  }
}

BENCHMARK(BM_OrderDataStore_addEntry_keyAlreadyExists);

static void BM_OrderDataStore_addEntry_keyAlreadyExists_zeroVolume(
    benchmark::State &state) {
  std::shared_ptr ptr =
      std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 0, 0);
  OrderDataStore dataStore{};
  dataStore.addEntry(ptr);
  for (auto _ : state) {
    dataStore.addEntry(ptr);
  }
}

BENCHMARK(BM_OrderDataStore_addEntry_keyAlreadyExists_zeroVolume);

// Define another benchmark
static void BM_BollingerBand_runStrat(benchmark::State &state) {
  BollingerBand band{};
  for (auto _ : state) band.runStrategy();
}

BENCHMARK(BM_BollingerBand_runStrat);

BENCHMARK_MAIN();

#include <arbitrage/Arbitrage.h>
#include <benchmark/benchmark.h>

#include <memory>

#include "bollingerBand/BollingerBand.h"
#include "dataManager/OrderData.h"
#include "dataManager/OrderDataStore.h"
#include "dataManager/OrderTypes.h"
#include "exchange/Exchange.h"
#include "ordering-system/exchangeExecutors/bitmex/BitmexOrderExecutor.h"
#include "tradingStrategies/TradingStrategy.h"

class OrderBookFixture : public benchmark::Fixture {
  int SIZE = 1000;

 public:
  OrderBook orderBook{Exchange::BITMEX};

  void SetUp(const ::benchmark::State &state) {
    OrderTypes::OrderType orderType;
    for (auto i = 0; i < SIZE; i++) {
      if (i % 2 == 0) {
        orderType = OrderTypes::ASK;
      } else {
        orderType = OrderTypes::BID;
      }
      std::shared_ptr ptr = std::make_shared<OrderData>(
          OrderTypes::ASK, Exchange::BITMEX, 500 + i, 100);
      orderBook.addEntry(ptr);
    }
  }

  void TearDown(const ::benchmark::State &state) {}
};

class OrderDataStoreFixture : public benchmark::Fixture {
  int SIZE = 1000;

 public:
  OrderDataStore orderDataStore{};

  void SetUp(const ::benchmark::State &state) {
    OrderTypes::OrderType orderType;
    for (auto i = 0; i < SIZE; i++) {
      if (i % 2 == 0) {
        orderType = OrderTypes::ASK;
      } else {
        orderType = OrderTypes::BID;
      }
      std::shared_ptr ptr = std::make_shared<OrderData>(
          orderType, Exchange::BITMEX, 500 + i, 100);
      orderDataStore.addEntry(ptr);
    }
  }

  void TearDown(const ::benchmark::State &state) {}
};

//// Define another benchmark
// static void BM_OrderExecutor_submitOrder(benchmark::State &state) {
//   Order order{"XBTUSD", 100, 5, true};
//   BinanceOrderExecutor executor{};
//   executor.enableBenchmarking();
//   executor.disableOutput();
//   //    executor.enableOutput();
//   for (auto _ : state) {
//     executor.submitOrder(order);
//   }
// }
//
// BENCHMARK(BM_OrderExecutor_submitOrder);
//
//// Define another benchmark
// BENCHMARK_F(OrderBookFixture, BM_OrderBook_getHighestBid)
//(benchmark::State &state) {
//   for (auto _ : state) {
//     orderBook.getHighestBid();
//   }
// }
//
//// Define another benchmark
// BENCHMARK_F(OrderBookFixture, BM_OrderBook_getLowestAsk)
//(benchmark::State &state) {
//   for (auto _ : state) {
//     orderBook.getLowestAsk();
//   }
// }
//
//// Define another benchmark
// BENCHMARK_F(OrderDataStoreFixture, BM_OrderDataStore_addEntry)
//(benchmark::State &state) {
//   std::shared_ptr ptr =
//       std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 600,
//       100);
//   for (auto _ : state) {
//     orderDataStore.addEntry(ptr);
//   }
// }
//
//// OrderDataStore but path where key already exists...but volume != 0
// BENCHMARK_F(OrderDataStoreFixture,
// BM_OrderDataStore_addEntry_keyAlreadyExists) (benchmark::State &state) {
//   std::shared_ptr ptr =
//       std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 200,
//       100);
//   orderDataStore.addEntry(ptr);
//   for (auto _ : state) {
//     orderDataStore.addEntry(ptr);
//   }
// }
// BENCHMARK_F(OrderDataStoreFixture,
//             BM_OrderDataStore_addEntry_keyAlreadyExists_zeroVolume)
//(benchmark::State &state) {
//   std::shared_ptr ptr =
//       std::make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 0, 0);
//   orderDataStore.addEntry(ptr);
//   for (auto _ : state) {
//     orderDataStore.addEntry(ptr);
//   }
// }
//
//// Define another benchmark
// static void BM_BollingerBand_runStrat(benchmark::State &state) {
//   BollingerBand band{};
//   for (auto _ : state) band.runStrategy();
// }
//
// BENCHMARK(BM_BollingerBand_runStrat);

// BENCHMARK_F(OrderBookFixture, TradingStrategy_Arbitrage_runStrategy)
//(benchmark::State &state) {
//   std::unique_ptr<TradingStrategy> arbitrage = make_unique<Arbitrage>();
//   for (auto _ : state) {
//     // Add two instances for arbitrage
//     arbitrage->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
//     arbitrage->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
//     arbitrage->runStrategy();
//   }
// }

BENCHMARK_F(OrderBookFixture, TradingStrategy_BollingerBand_runStrategy)
(benchmark::State &state) {
  std::unique_ptr<TradingStrategy> bollingerBand = make_unique<BollingerBand>();
  for (auto _ : state) {
    // Add two instances for arbitrage
    //    bollingerBand->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
    //    bollingerBand->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
    //    bollingerBand->runStrategy();
    bollingerBand->buy(std::make_shared<OrderData>(OrderTypes::OrderType::ASK,
                                                   Exchange::BITMEX, 100, 100));
  }
}

BENCHMARK_F(OrderBookFixture, TradingStrategy_insertNewOrderBook)
(benchmark::State &state) {
  std::unique_ptr<TradingStrategy> bollingerBand = make_unique<BollingerBand>();
  for (auto _ : state) {
    bollingerBand->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
  }
}

/* TradingStrategy.h
virtual void newData(std::shared_ptr<OrderData>) = 0;
virtual void runStrategy() = 0;
void executeBuy(std::shared_ptr<OrderData> data);
void executeSell(std::shared_ptr<OrderData> data);
virtual void buy(std::shared_ptr<OrderData>);
virtual void sell(std::shared_ptr<OrderData>);
void insertNewOrderBook(std::shared_ptr<OrderBook>);
 */

BENCHMARK_MAIN();

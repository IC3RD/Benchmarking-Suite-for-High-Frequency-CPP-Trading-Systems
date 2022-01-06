#include <arbitrage/Arbitrage.h>
#include <benchmark/benchmark.h>
#include <orderDataCollectors/OrderDataCollector.h>

#include <memory>

#include "bollingerBand/BollingerBand.h"
#include "dataManager/OrderData.h"
#include "dataManager/OrderDataStore.h"
#include "dataManager/OrderTypes.h"
#include "exchange/Exchange.h"
#include "orderDataCollectors/marketInfoListener/BinanceListener.h"
#include "ordering-system/exchangeExecutors/bitmex/BitmexOrderExecutor.h"
#include "tradingStrategies/TradingStrategy.h"

class OrderBookFixture : public benchmark::Fixture {
  int SIZE = 1000;

 public:
  OrderBook orderBook{Exchange::BITMEX};

  void SetUp(const ::benchmark::State &state) {
    OrderTypes::OrderType orderType;
    double price = 500;
    for (auto i = 0; i < SIZE; i++) {
      if (i % 2 == 0) {
        orderType = OrderTypes::ASK;
        price = price + i;
      } else {
        orderType = OrderTypes::BID;
        price = price - i;
      }
      std::shared_ptr ptr =
          std::make_shared<OrderData>(orderType, Exchange::BITMEX, price, 100);
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

#if defined(ENABLE_CPP_BENCHMARKS) && !defined(BENCHMARK_HOTPATH)
/* Benchmarking ExchangeOrderExecutor implementations: */

// *** START of Binance ***
static void ExchangeOrderExecutor_BinanceOrderExecutor_parseOrder(
    benchmark::State &state) {
  Order order{"XBTUSD", 100, 5, true};
  BinanceOrderExecutor executor{};
  executor.disableOutput();
  for (auto _ : state) {
    executor.parseOrder(order);
  }
};

BENCHMARK(ExchangeOrderExecutor_BinanceOrderExecutor_parseOrder);

static void ExchangeOrderExecutor_BinanceOrderExecutor_authenticate(
    benchmark::State &state) {
  BinanceOrderExecutor executor{};
  executor.disableOutput();
  for (auto _ : state) {
    executor.authenticate("Dummy Message");
  }
}

BENCHMARK(ExchangeOrderExecutor_BinanceOrderExecutor_authenticate);

static void ExchangeOrderExecutor_BinanceOrderExecutor_generateTimestamp(
    benchmark::State &state) {
  BinanceOrderExecutor executor{};
  executor.disableOutput();
  for (auto _ : state) {
    executor.generateTimestamp();
  }
}

BENCHMARK(ExchangeOrderExecutor_BinanceOrderExecutor_generateTimestamp);

static void ExchangeOrderExecutor_BinanceOrderExecutor_generateHeaders(
    benchmark::State &state) {
  BinanceOrderExecutor executor{};
  executor.disableOutput();
  for (auto _ : state) {
    executor.generateHeaders();
  }
}

BENCHMARK(ExchangeOrderExecutor_BinanceOrderExecutor_generateHeaders);

// This benchmarks the entire BinanceOrderExecutor 'hotpath'.
// Make sure to compile with -DENABLE_CPP_BENCHMARKS
// This function will not execute otherwise.
static void ExchangeOrderExecutor_BinanceOrderExecutor_submitOrder(
    benchmark::State &state) {
  Order order{"XBTUSD", 100, 5, true};
  BinanceOrderExecutor executor{};
  executor.disableOutput();
  for (auto _ : state) {
    executor.submitOrder(order);
  }
}

BENCHMARK(ExchangeOrderExecutor_BinanceOrderExecutor_submitOrder);

// *** END of Binance ***
/* End of benchmarking ExchangeOrderExecutors */

/* Benchmarking TradingStrategy */

BENCHMARK_F(OrderBookFixture, TradingStrategy_BollingerBand_newData_runStrategy)
(benchmark::State &state) {
  std::unique_ptr<TradingStrategy> bollingerBand = make_unique<BollingerBand>();
  std::shared_ptr<OrderData> data =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 505, 100);
  for (auto _ : state) {
    bollingerBand->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
    bollingerBand->newData(data);
    // newData will implicitly call runStrategy
  }
}

// This is an example with one order book. Add more order books to test
// insertion.
BENCHMARK_F(OrderBookFixture, TradingStrategy_insertNewOrderBook)
(benchmark::State &state) {
  std::unique_ptr<TradingStrategy> bollingerBand = make_unique<BollingerBand>();
  for (auto _ : state) {
    bollingerBand->insertNewOrderBook(std::make_shared<OrderBook>(orderBook));
  }
}

/* End of benchmarking TradingStrategy */

/* OrderBook */
BENCHMARK_F(OrderBookFixture, OrderBook_addTradingStrategy)
(benchmark::State &state) {
  std::shared_ptr<TradingStrategy> bollingerBand = make_shared<BollingerBand>();
  for (auto _ : state) {
    orderBook.addTradingStrategy(bollingerBand);
  }
}

BENCHMARK_F(OrderBookFixture, OrderBook_addEntry)
(benchmark::State &state) {
  std::shared_ptr<OrderData> data =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 505, 100);
  for (auto _ : state) {
    orderBook.addEntry(data);
  }
}

BENCHMARK_F(OrderBookFixture, OrderBook_getHighestBid)
(benchmark::State &state) {
  for (auto _ : state) {
    orderBook.getHighestBid();
  }
}

BENCHMARK_F(OrderBookFixture, OrderBook_getLowestAsk)
(benchmark::State &state) {
  for (auto _ : state) {
    orderBook.getLowestAsk();
  }
}

/* End of benchmarking OrderBook */

/* OrderDataStore */
BENCHMARK_F(OrderDataStoreFixture, OrderDataStore_addEntry)
(benchmark::State &state) {
  std::shared_ptr<OrderData> data =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 505, 100);
  for (auto _ : state) {
    orderDataStore.addEntry(data);
  }
}
/* End OrderDataStore */
#endif

#if defined(BENCHMARK_HOTPATH) && !defined(ENABLE_CPP_BENCHMARKS)
BENCHMARK_F(OrderBookFixture, benchmark_hotpath)
(benchmark::State &state) {
  std::shared_ptr<OrderBook> binanceOrderBook =
      std::make_shared<OrderBook>(Exchange::BINANCE);

  std::shared_ptr<BollingerBand> strategy = std::make_shared<BollingerBand>();

  strategy->insertNewOrderBook(binanceOrderBook);
  strategy->addExchange(Exchange::BINANCE);

  binanceOrderBook->addTradingStrategy(strategy);

  std::shared_ptr<OrderData> data1 =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 600, 100);
  std::shared_ptr<OrderData> data2 =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 550, 100);
  binanceOrderBook->addEntry(data1);
  binanceOrderBook->addEntry(data2);

  std::shared_ptr<OrderData> newDataFromExchange =
      make_shared<OrderData>(OrderTypes::ASK, Exchange::BINANCE, 490, 100);

  for (auto _ : state) {
    // Will trigger a buy.
    binanceOrderBook->addEntry(newDataFromExchange);
  }
}
#endif

BENCHMARK_MAIN();

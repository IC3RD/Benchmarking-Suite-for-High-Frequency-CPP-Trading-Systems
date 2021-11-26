//#include <../include/benchmark/include/benchmark/benchmark.h>

#include <benchmark/benchmark.h>
#include "dataManager/OrderDataStore.h"
#include "bollingerBand/BollingerBand.h"
#include "exchange/OrderTypes.h"
#include "exchange/Exchange.h"
#include "exchange/OrderData.h"
#include "exchange/TradingStrategy.h"
#include "ordering-system/bitmex/BitmexOrderExecutor.h"


// Define another benchmark
static void BM_OrderExecutor_submitOrder(benchmark::State &state) {
    Order order {"XBTUSD", 100, 5, true};
    BinanceOrderExecutor executor {};
    executor.enableBenchmarking();
//    executor.enableOutput();
    for (auto _: state) {
        executor.submitOrder(order);
    }
}
BENCHMARK(BM_OrderExecutor_submitOrder);
// since submitOrder is very slow due to curl we benchmark all the function it calls instead:
// calls parseOrder, getUrl, authenticate, generateHeaders, sendOrder

static void BM_OrderExecutor_parseOrder(benchmark::State &state) {
    Order order {"XBTUSD", 100, 5, true};
    BinanceOrderExecutor executor {};
    executor.enableBenchmarking();
//    executor.enableOutput();
    for (auto _: state) {
        executor.parseOrder(order);
    }
}
BENCHMARK(BM_OrderExecutor_parseOrder);

static void BM_OrderExecutor_getUrl(benchmark::State &state) {
    BinanceOrderExecutor executor {};
    executor.enableBenchmarking();
//    executor.enableOutput();
    for (auto _: state) {
        executor.getURL();
    }
}
BENCHMARK(BM_OrderExecutor_getUrl);

static void BM_OrderExecutor_authenticate(benchmark::State &state) {
    std::string message = "this is a test for benchmarking";
    BinanceOrderExecutor executor {};
    executor.enableBenchmarking();
//    executor.enableOutput();
    for (auto _: state) {
        executor.authenticate(message);
    }
}
BENCHMARK(BM_OrderExecutor_authenticate);

//this one also uses curl mainly so might not need it
static void BM_OrderExecutor_generateHeaders(benchmark::State &state) {
    struct curl_slist *chunk = nullptr;
    BinanceOrderExecutor executor {};
    executor.enableBenchmarking();
//    executor.enableOutput();
    for (auto _: state) {
        executor.generateHeaders(&chunk);
    }
}
BENCHMARK(BM_OrderExecutor_generateHeaders);
//sendOrder is only using curl so makes no sense to include it

// Define another benchmark
static void BM_OrderBook_getHighestBid(benchmark::State &state) {
    OrderBook book{Exchange::BITMEX};
    for (auto _: state) {
        book.getHighestBid();
    }
}

BENCHMARK(BM_OrderBook_getHighestBid);

// Define another benchmark
static void BM_OrderBook_getLowestAsk(benchmark::State &state) {
    OrderBook book{Exchange::BITMEX};
    for (auto _: state) {
        book.getLowestAsk();
    }
}

BENCHMARK(BM_OrderBook_getLowestAsk);

// Define another benchmark
static void BM_OrderDataStore_addEntry(benchmark::State &state) {
    // OrderTypes::OrderType type, Exchange::ExchangeName name, long price,
    //            double volume
//    OrderData test_data {OrderTypes::ASK, Exchange::BITMEX, 500, 100};
    std::shared_ptr ptr = make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 500, 100);
    OrderDataStore dataStore{};
    for (auto _: state) {
        dataStore.addEntry(ptr);

    }
}

BENCHMARK(BM_OrderDataStore_addEntry);

// OrderDataStore but path where key already exists...but volume != 0
static void BM_OrderDataStore_addEntry_keyAlreadyExists(benchmark::State &state) {
    std::shared_ptr ptr = make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 500, 100);
    OrderDataStore dataStore{};
   dataStore.addEntry(ptr);
   for (auto _: state) {
        dataStore.addEntry(ptr);
    }
}

BENCHMARK(BM_OrderDataStore_addEntry_keyAlreadyExists);

static void BM_OrderDataStore_addEntry_keyAlreadyExists_zeroVolume(benchmark::State &state) {
    std::shared_ptr ptr = make_shared<OrderData>(OrderTypes::ASK, Exchange::BITMEX, 0, 0);
    OrderDataStore dataStore{};
    dataStore.addEntry(ptr);
    for (auto _: state) {
        dataStore.addEntry(ptr);
    }
}

BENCHMARK(BM_OrderDataStore_addEntry_keyAlreadyExists_zeroVolume);

// Define another benchmark
static void BM_BollingerBand_runStrat(benchmark::State &state) {
    BollingerBand band{};
    for (auto _: state)
        band.runStrategy();
}

BENCHMARK(BM_BollingerBand_runStrat);

BENCHMARK_MAIN();

cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderExecutor.h
        exchangeExecutors/coinbase/CoinbaseOrderExecutor.h
        exchangeExecutors/coinbase/CoinbaseOrderExecutor.cpp exchangeExecutors/utils/Base64.h
        exchangeExecutors/bitmex/BitmexOrderExecutor.cpp
        exchangeExecutors/bitmex/BitmexOrderExecutor.h
        exchangeExecutors/utils/SHA256Engine.h
        exchangeExecutors/utils/SHA256Engine.cpp
        exchangeExecutors/binance/BinanceOrderExecutor.cpp
        exchangeExecutors/binance/BinanceOrderExecutor.h
        OrderManager.cpp
        OrderManager.h
        exchangeExecutors/ExchangeOrderExecutor.h
        exchangeExecutors/ExchangeOrderExecutor.cpp exchangeExecutors/utils/CurlManager.cpp exchangeExecutors/utils/CurlManager.h)

add_library(ordering-system ${SOURCE_FILES})

target_include_directories(ordering-system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ordering-system PUBLIC tradingStrategies JSON curl
        benchmarking)

#add_subdirectory(coinbase)

# add a 'debug' executable file so we don't have to run main to test our code.
add_executable(debug exchangeExecutors/debug.cpp)

target_link_libraries(debug ordering-system)

install(TARGETS debug DESTINATION ${INSTALL_BIN_DIR})



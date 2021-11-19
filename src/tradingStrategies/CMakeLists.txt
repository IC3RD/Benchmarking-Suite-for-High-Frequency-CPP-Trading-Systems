cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES arbitrage/Arbitrage.cpp bollingerBand/BollingerBand.cpp bollingerBand/Band.cpp
        TradingStrategy.h TradingStrategy.cpp)

add_library(tradingStrategies ${SOURCE_FILES})

target_include_directories(tradingStrategies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tradingStrategies PUBLIC
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        exchange
        dataManager
        ordering-system)
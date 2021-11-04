cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES Order.cpp MarketData.cpp Exchange.h TradingStrategy.cpp)

add_library(exchange ${SOURCE_FILES})

target_link_libraries(exchange PUBLIC
        JSON
        dataManager
        ordering-system)


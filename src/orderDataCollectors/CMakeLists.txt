cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderDataCollector.cpp ../tradingStrategies/TradingStrategy.cpp)

add_library(orderDataCollectors ${SOURCE_FILES})

add_subdirectory(marketInfoListener)
add_subdirectory(fileReaderListener)

target_link_libraries(orderDataCollectors PUBLIC
        curl
        ixwebsocket
        tradingStrategies
        JSON)

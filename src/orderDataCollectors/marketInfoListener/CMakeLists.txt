cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES Listener.cpp BitMEXListener.cpp BinanceListener.cpp CoinbaseListener.cpp
        FTXListener.cpp KrakenListener.cpp ../OrderDataCollector.cpp ../../tradingStrategies/TradingStrategy.cpp)

add_library(listener ${SOURCE_FILES})

target_link_libraries(listener PUBLIC
        curl
        ixwebsocket
        tradingStrategies
        JSON)

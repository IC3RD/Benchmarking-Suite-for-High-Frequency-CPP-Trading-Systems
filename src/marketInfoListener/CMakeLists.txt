cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES BitMEXListener.cpp BinanceListener.cpp CoinbaseListener.cpp)

add_library(listener ${SOURCE_FILES})

target_link_libraries(listener PUBLIC
    ixwebsocket
    bollingerBand
    JSON)

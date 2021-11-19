cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES FileReaderListener.cpp ../OrderDataCollector.cpp)

add_library(fileListener ${SOURCE_FILES})

target_link_libraries(fileListener PUBLIC
        curl
        ixwebsocket
        tradingStrategies
        JSON)

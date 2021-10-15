cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES BollingerBand.cpp Logger.cpp MarketData.cpp AlgoTrader.cpp)


add_executable(trader ${SOURCE_FILES})
install(TARGETS trader DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})

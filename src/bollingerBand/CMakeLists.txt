cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES BollingerBand.cpp Logger.cpp MarketData.cpp AlgoTrader.cpp Order.cpp BitMEXApi.cpp SHA256Engine.cpp SHA256Engine.h)


# add_executable(trader ${SOURCE_FILES})
# install(TARGETS trader DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
add_library(bollingerBand ${SOURCE_FILES})

target_link_libraries(bollingerBand PUBLIC
        Foundation
        Crypto
        Util
        JSON
        NetSSL)
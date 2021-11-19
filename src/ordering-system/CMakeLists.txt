cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderExecutor.cpp OrderExecutor.h
        coinbase/CoinbaseOrderExecutor.h
        coinbase/CoinbaseOrderExecutor.cpp utils/Base64.h
        bitmex/BitmexOrderExecutor.cpp
        bitmex/BitmexOrderExecutor.h
        utils/SHA256Engine.h
        utils/SHA256Engine.cpp
        binance/BinanceOrderExecutor.cpp
        binance/BinanceOrderExecutor.h
        OrderManager.cpp
        OrderManager.h
        )

add_library(ordering-system ${SOURCE_FILES})

target_include_directories(ordering-system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ordering-system PUBLIC bollingerBand JSON curl)

#add_subdirectory(coinbase)

# add a 'debug' executable file so we don't have to run main to test our code.
add_executable(debug debug.cpp)

target_link_libraries(debug ordering-system)

install(TARGETS debug DESTINATION ${INSTALL_BIN_DIR})



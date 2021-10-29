cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderManager.cpp OrderManager.h OrderBuilder.cpp
        OrderBuilder.h
        coinbase/CoinbaseOrderManager.h
        coinbase/CoinbaseOrderManager.cpp utils/Base64.h
        bitmex/BitmexOrderManager.cpp
        bitmex/BitmexOrderManager.h
        utils/SHA256Engine.h
        utils/SHA256Engine.cpp)

add_library(ordering-system ${SOURCE_FILES})

target_include_directories(ordering-system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ordering-system PUBLIC bollingerBand JSON curl)

#add_subdirectory(coinbase)

# add a 'debug' executable file so we don't have to run main to test our code.
add_executable(debug debug.cpp)

target_link_libraries(debug ordering-system)

install(TARGETS debug DESTINATION ${INSTALL_BIN_DIR})



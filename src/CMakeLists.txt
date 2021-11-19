cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})

target_link_libraries(main PUBLIC
        ixwebsocket
        listener
        dataManager
        exchange
        tradingStrategies
        ordering-system
        #concurrentUnorderedSet
        curl
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        OpenSSL::SSL
        )

add_subdirectory(tradingStrategies)
add_subdirectory(orderDataCollectors)
add_subdirectory(dataManager)
add_subdirectory(concurrentUnorderedSet)
add_subdirectory(exchange)
add_subdirectory(ordering-system)

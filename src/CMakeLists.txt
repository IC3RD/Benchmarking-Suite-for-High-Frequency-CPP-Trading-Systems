cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})

target_link_libraries(main PUBLIC
        ixwebsocket
        bollingerBand
        listener
        dataManager
        exchange
        ordering-system
        #concurrentUnorderedSet
        curl
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        OpenSSL::SSL
        #ordering-system
        )

add_subdirectory(bollingerBand)
add_subdirectory(marketInfoListener)
add_subdirectory(dataManager)
add_subdirectory(ConcurrentUnorderedSet)
add_subdirectory(exchange)
add_subdirectory(ordering-system)

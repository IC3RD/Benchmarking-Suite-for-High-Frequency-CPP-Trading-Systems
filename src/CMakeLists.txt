cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})

find_package(Poco REQUIRED Foundation Crypto Util JSON NetSSL)

target_link_libraries(main PUBLIC ixwebsocket bollingerBand curl Poco::Foundation
        Poco::Crypto
        Poco::Util
        Poco::JSON
        Poco::NetSSL)

add_subdirectory(bollingerBand)

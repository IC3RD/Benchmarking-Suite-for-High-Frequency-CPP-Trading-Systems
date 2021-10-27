cmake_minimum_required(VERSION 3.2)

set(CC /usr/local/bin/gcc-10)
set(CXX /usr/local/bin/g++-10)
set(CMAKE_C_COMPILER /usr/local/bin/gcc-10)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-10)

project(CPPDesignPatternsLowLatency)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(POCO_DIR lib/Poco)
set(POCO_INCLUDE_DIRS
        "${POCO_DIR}/ApacheConnector/include"
        "${POCO_DIR}/CppParser/include"
        "${POCO_DIR}/CppUnit/include"
        "${POCO_DIR}/Crypto/include"
        "${POCO_DIR}/Data/include"
        "${POCO_DIR}/Encodings/include"
        "${POCO_DIR}/Foundation/include"
        "${POCO_DIR}/JSON/include"
        "${POCO_DIR}/MongoDB/include"
        "${POCO_DIR}/Net/include"
        "${POCO_DIR}/NetSSL_OpenSSL/include"
        "${POCO_DIR}/NetSSL_Win/include"
        "${POCO_DIR}/openssl/build/include"
        "${POCO_DIR}/PDF/include"
        "${POCO_DIR}/Redis/include"
        "${POCO_DIR}/SevenZip/include"
        "${POCO_DIR}/Util/include"
        "${POCO_DIR}/XML/include"
        "${POCO_DIR}/Zip/include"
)

include_directories(${INSTALL_INCLUDE_DIR})
include_directories(${INSTALL_LIB_DIR})

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${POCO_INCLUDE_DIRS})


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib)


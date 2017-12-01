cmake_minimum_required(VERSION 3.8)
project(ESAIP_RANSOM)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES client/main.cpp client/encrypt.cpp client/decrypt.cpp)
add_executable(ESAIP_RANSOM ${SOURCE_FILES} client/encrypt.cpp client/decrypt.cpp)
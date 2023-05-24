cmake_minimum_required(VERSION 3.2)
project(HelloWorldProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(micro_service
    mirco_service.cpp
    settings/settings.cpp
    Cleaner/cleaner.cpp
    Compressor/compressor.cpp
    Decompressor/decompressor.cpp
    Requests/requests.cpp
    Compression/compression.cpp
    FileUtils/file_utils.cpp
)

find_package(Boost REQUIRED chrono)

target_link_libraries(micro_service
    -lpqxx -lpq -pthread -lboost_thread -lboost_chrono -lZipper -lz
)
# All services

add_definitions(-D USED_DOCKER)

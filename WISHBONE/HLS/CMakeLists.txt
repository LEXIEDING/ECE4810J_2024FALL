cmake_minimum_required(VERSION 3.26)
project(HLS)

set(CMAKE_CXX_STANDARD 14)

add_executable(HLS
        hls_top_v3.cpp
        test_hls_top_v3.cpp
        )

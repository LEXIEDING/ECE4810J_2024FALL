cmake_minimum_required(VERSION 3.26)
project(HLS)

set(CMAKE_CXX_STANDARD 14)

add_executable(HLS
        hls_top.cpp
        test_hls_top.cpp
        # hls_top_v1.cpp
        # test_hls_top_v1.cpp
        # hls_alu.cpp
        # test_hls_alu.cpp
        )

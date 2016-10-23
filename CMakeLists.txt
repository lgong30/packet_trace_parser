cmake_minimum_required(VERSION 3.6)
project(packet_trace_parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES packet_trace_parser.cpp packet_trace_parser.h)
add_executable(packet_trace_parser ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.16)
project(complex-array LANGUAGES CXX)

add_library(complex_array STATIC complex_array.cpp)
target_include_directories(complex_array PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(complex_array PRIVATE cxx_std_17)

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    message(STATUS "Tests are enabled")
    enable_testing()
    add_subdirectory(tests)
else()
    message(STATUS "Tests are disabled.")
endif()

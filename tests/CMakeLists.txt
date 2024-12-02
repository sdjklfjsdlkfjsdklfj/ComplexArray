find_package(GTest REQUIRED)
add_executable(complex_array_test complex_array_test.cpp)
target_link_libraries(complex_array_test PRIVATE complex_array GTest::Main)
include(GoogleTest)
gtest_discover_tests(complex_array_test)


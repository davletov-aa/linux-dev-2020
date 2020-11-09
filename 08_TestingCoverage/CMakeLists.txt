cmake_minimum_required(VERSION 3.13)
project(08_TestingCoverage C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0  -fprofile-arcs -ftest-coverage")

add_library(testing_coverage STATIC buf.c)

add_executable(tests tests.c)
target_link_libraries(tests testing_coverage)

include(CTest)

add_test(test_buffer_push_and_free tests 0)
add_test(test_buffer_init tests 1)
add_test(test_buffer_push tests 2)
add_test(test_buffer_clear_empty tests 3)
add_test(test_buffer_clear_not_empty tests 4)
add_test(test_buffer_pop tests 5)
add_test(test_buffer_grow_and_trunc tests 6)

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake CTestTestfile.cmake  DartConfiguration.tcl  Makefile  Testing libtesting_coverage.a tests)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests)
add_custom_target(check_coverage COMMAND make ExperimentalCoverage DEPENDS check)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES ModelTest.cpp)

add_executable(RunAllTests ${SOURCE_FILES})

target_link_libraries(RunAllTests gtest gtest_main)
target_link_libraries(RunAllTests SolitaireKlondike_lib)
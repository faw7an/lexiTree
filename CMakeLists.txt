cmake_minimum_required(VERSION 3.20)
project(EnglishParser CXX)
set(CMAKE_CXX_STANDARD 17)

# Make FetchContent available
include(FetchContent)

# Main executable source files
set(SOURCE_FILES
    src/main.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    # Add parser files here in later phases
    # src/top_down_parser.cpp
    # src/bottom_up_parser.cpp
    # src/parse_tree.cpp
    # src/symbol_table.cpp
    # src/display.cpp
)

add_executable(english-parser ${SOURCE_FILES})
target_include_directories(english-parser PRIVATE include)

# Tests
enable_testing()

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    tests/test_lexer.cpp
    # tests/test_top_down.cpp
    # tests/test_bottom_up.cpp
    # tests/test_symbol_table.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    # src/top_down_parser.cpp
    # src/bottom_up_parser.cpp
    # src/parse_tree.cpp
    # src/symbol_table.cpp
    # src/display.cpp
)
target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests GTest::gtest_main)

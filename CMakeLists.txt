cmake_minimum_required(VERSION 3.10)
project(LinearSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add source files
add_library(
    LinearSystem 
    src/LinearSystem.cpp 
    src/StateTransitionMatrix.cpp
    src/DesignMatrix.cpp 
)

# Find Google Test
find_package(GTest REQUIRED)

# Add unit tests
add_executable(UnitTests UnitTest/test_LinearSystem.cpp)
target_link_libraries(UnitTests LinearSystem GTest::gtest_main)
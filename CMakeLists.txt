cmake_minimum_required(VERSION 3.10)
project(LinearSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

option(COVERAGE "Enable coverage reporting" ON)

if(COVERAGE)
  message(STATUS "Building with code coverage flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
endif()

# Include directories
include_directories(include)
include_directories(/opt/homebrew/include/eigen3) 

# Find required libraries
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Add source files
add_library(
    LinearSystem 
    src/LinearSystem.cpp 
    src/StateTransitionMatrix.cpp
    src/DesignMatrix.cpp 
    src/ProcessNoiseCov.cpp
)

# Add unit tests
add_executable(UnitTests UnitTest/test_LinearSystem.cpp)
target_link_libraries(UnitTests LinearSystem GTest::gtest_main)
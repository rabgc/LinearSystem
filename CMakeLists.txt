cmake_minimum_required(VERSION 3.10)
project(LinearSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add source files
add_library(LinearSystem src/LinearSystem.cpp src/StateTransitionMatrix.cpp)

# Find Google Test
find_package(GTest REQUIRED)
if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    link_directories(${GTEST_LIBRARIES_DIR})
else()
    # Fallback to manually specifying paths if GTest is not found
    include_directories(/opt/homebrew/opt/googletest/include)
    link_directories(/opt/homebrew/opt/googletest/lib)
endif()

# Add unit tests
add_executable(UnitTests UnitTest/test_LinearSystem.cpp)
target_link_libraries(UnitTests LinearSystem ${GTEST_LIBRARIES} pthread)
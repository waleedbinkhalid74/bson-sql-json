cmake_minimum_required(VERSION 3.16)

#----------------------------------------
# Project make and meta data
#----------------------------------------
project(Bson-Sql-Json)

#----------------------------------------
# Binary destinations
#----------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#----------------------------------------
# Create binary destination directories if not exist
#----------------------------------------
file(MAKE_DIRECTORY
    ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

#----------------------------------------
# Sub-directories
#----------------------------------------
add_subdirectory(src)

#----------------------------------------
# C++ Standard as google test requirement
#----------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------------------------
# Fetch GoogleTest
#----------------------------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#----------------------------------------
# Setup testing pipeline
#----------------------------------------
enable_testing()
add_test(NAME test_run COMMAND test_example)

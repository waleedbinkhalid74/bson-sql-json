cmake_minimum_required(VERSION 3.16)

#----------------------------------------
# Project make and meta data
#----------------------------------------
project(Bson-Sql-Json)

#----------------------------------------
# Binary destinations
#----------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

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
add_subdirectory(bson)
add_subdirectory(examples)

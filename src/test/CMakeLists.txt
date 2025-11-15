#----------------------------------------
# Source Files
#----------------------------------------
set(test_source
    RunTest.cpp
    bson/TestExample.cpp
)

set(test_function_source
    RunTest.cpp
    functions/TestJsonValue.cpp
)

#----------------------------------------
# Executables
#----------------------------------------
add_executable(test_example
    ${test_source}
)

add_executable(test_functions
    ${test_function_source}
)

#----------------------------------------
# Link libraries
#----------------------------------------
target_link_libraries(test_example
    PRIVATE
    bson
    gtest_main
)

target_link_libraries(test_functions
    PRIVATE
    bson
    functions
    gtest_main
)

#----------------------------------------
# Set output directory for this executable only
#----------------------------------------
set_target_properties(test_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/gtest
)

set_target_properties(test_functions PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/gtest
)

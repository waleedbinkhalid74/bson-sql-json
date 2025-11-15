#----------------------------------------
# Source Files
#----------------------------------------
set(test_source
    RunTest.cpp
    bson/TestExample.cpp
)

#----------------------------------------
# Executables
#----------------------------------------
add_executable(test ${test_source}
)

#----------------------------------------
# Link libraries
#----------------------------------------
target_link_libraries(test
    PRIVATE
    bson    
    gtest_main  
)

#----------------------------------------
# Set output directory for this executable only
#----------------------------------------
set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../gtest
)

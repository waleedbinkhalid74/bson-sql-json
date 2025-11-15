#----------------------------------------
# Source Files
#----------------------------------------
set(example_source
    example1.cpp
)

#----------------------------------------
# Executables
#----------------------------------------
add_executable(example1 ${example_source}
)

#----------------------------------------
# Link libraries
#----------------------------------------
target_link_libraries(example1
    PUBLIC
    bson    
)

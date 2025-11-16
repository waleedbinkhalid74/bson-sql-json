#----------------------------------------
# Source Files
#----------------------------------------
set(functions_source
    JsonValue.cpp
    parser/PathExpr.cpp
)


#----------------------------------------
# Library
#----------------------------------------
add_library(functions STATIC ${functions_source})

#----------------------------------------
# Link Libraries
#----------------------------------------
target_link_libraries(functions
    PRIVATE
        bson
)

#----------------------------------------
# Include directories
#----------------------------------------
target_include_directories(functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

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
# Include directories
#----------------------------------------
target_include_directories(functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

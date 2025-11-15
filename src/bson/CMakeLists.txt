
#----------------------------------------
# Source Files
#----------------------------------------

# ../bson/json.cpp ../bson/bson.cpp ../bson/time_support.cpp ../bson/parse_number.cpp  ../bson/base64.cpp 
set(bson_source
    base64.cpp
    bson.cpp
    hex.cpp
    json.cpp
    parse_number.cpp
    time_support.cpp
    valid.cpp
)

#----------------------------------------
# Library
#----------------------------------------
add_library(bson STATIC ${bson_source})

#----------------------------------------
# Include directories
#----------------------------------------
target_include_directories(bson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

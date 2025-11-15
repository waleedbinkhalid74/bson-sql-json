/**
 * @file JsonValue.cpp
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "functions/JsonValue.h"

namespace funcs {

template <typename T>
T jsonValue(const bsonobj& element, std::string_view path) {
    return std::string("Hello World");
}

template std::string jsonValue<std::string>(const bsonobj& element, std::string_view path);
}  // namespace funcs

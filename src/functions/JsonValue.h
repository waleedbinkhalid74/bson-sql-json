/**
 * @file JsonValue.h
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include <optional>
#include <string>
#include <string_view>

#include "ErrorHandlingMode.h"
#include "bson/bsonelement.h"
#include "bson/bsontypes.h"

using namespace _bson;

namespace funcs {

/**
 * @brief Extracts the value from a BSON object based on the provided JSON path.
 * This is similar to the JSON_VALUE function as per SQL/JSON standard.
 * @tparam T return type similar to RETURNING <type> clause in SQL/JSON standard
 * @param element BSON object from which to extract the value
 * @param path JSON path expression as per SQL/JSON standard
 * @param mode Error handling mode (RETURN_NULL or ERROR)
 * @return std::optional<T> Extracted value of type T if found, if error handling mode is RETURN_NULL and path not found, returns std::nullopt
 * otherwise throws PathNotFoundError exception
 */
template <typename T>
std::optional<T> jsonValue(const bsonobj& element, std::string_view path, ErrorHandlingMode mode = ErrorHandlingMode::ERROR);

template <typename T>
std::optional<T> jsonValue(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode = ErrorHandlingMode::ERROR);

}  // namespace funcs
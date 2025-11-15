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
#include <string>
#include <string_view>

#include "bson/bsonelement.h"
#include "bson/bsontypes.h"

using namespace _bson;

namespace funcs {

template <typename T>
T jsonValue(const bsonobj& element, std::string_view path);

}  // namespace funcs
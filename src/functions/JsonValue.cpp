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

#include <optional>

#include "bson/bsonobj.h"
#include "bson/bsonobjbuilder.h"
#include "bson/json.h"
#include "functions/Exception.h"
#include "parser/PathExpr.h"

using namespace _bson;

namespace {
template <typename T>
[[nodiscard]] std::optional<T> handleInvalidTypeConvesion(ErrorHandlingMode mode) {
    if (mode == ErrorHandlingMode::RETURN_NULL) {
        return std::nullopt;
    }
    throw funcs::InvalidTypeConversionError();
}

template <typename T>
[[nodiscard]] std::optional<T> handleTypeConversion(const bsonelement& element, ErrorHandlingMode mode) {
    if constexpr (std::is_same<T, std::string>::value) {
        if (element.mayEncapsulate() || element.type() != BSONType::String) {
            if (element.isBoolean()) {
                std::string s = element.boolean() ? "true" : "false";
                return s;
            }
            return handleInvalidTypeConvesion<T>(mode);
        }
        return element.String();
    } else if constexpr ((std::is_integral<T>::value || std::is_floating_point<T>::value) && !std::is_same_v<T, bool>) {
        if (!element.isNumber()) {
            if (element.type() == BSONType::String) {
                // try to parse number from string
                std::string strVal = element.String();
                try {
                    if constexpr (std::is_integral<T>::value) {
                        return static_cast<T>(std::stoll(strVal));
                    } else if constexpr (std::is_floating_point<T>::value) {
                        return static_cast<T>(std::stod(strVal));
                    }
                } catch (const std::exception&) {
                    return handleInvalidTypeConvesion<T>(mode);
                }
            }
            return handleInvalidTypeConvesion<T>(mode);
        }
        if constexpr (std::is_floating_point<T>::value) {
            return static_cast<T>(element.numberDouble());
        }
        return static_cast<T>(element.numberLong());
    } else if constexpr (std::is_same<T, bool>::value) {
        if (element.type() != BSONType::Bool) {
            if (element.type() == BSONType::String) {
                auto iequals = [](std::string_view a, std::string_view b) {
                    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin(), [](unsigned char c1, unsigned char c2) {
                               return std::tolower(c1) == std::tolower(c2);
                           });
                };

                if (iequals(element.String(), "true")) {
                    return true;
                }
                if (iequals(element.String(), "false")) {
                    return false;
                }
            }
            return handleInvalidTypeConvesion<T>(mode);
        }
        return element.boolean();
    } else {
        return handleInvalidTypeConvesion<T>(mode);
    }
}
}  // namespace

namespace funcs {
template <typename T>
std::optional<T> jsonValue(const bsonobj& element, std::string_view path, ErrorHandlingMode mode) {
    PathExpr pathExpr(path);
    bsonobj currentObj = element;
    bsonelement currentElement;
    for (size_t i = 0; i < pathExpr.getSize(); ++i) {
        const auto& tokenPair = pathExpr.getToken(i);
        const std::string& tokenStr = tokenPair.first;
        const PathToken& tokenType = tokenPair.second;

        if (tokenType == PathToken::FIELD || tokenType == PathToken::ARRAY_INDEX) {
            currentElement = currentObj.getField(tokenStr);
            if (currentElement.isObject()) {
                currentObj = currentElement.object();
            }
            if (currentElement.eoo()) {
                // Field not found
                if (mode == ErrorHandlingMode::RETURN_NULL) {
                    return std::nullopt;
                } else {
                    throw PathNotFoundError(std::string(path));
                }
            }
        }
    }

    // element has been found, now handle type conversion
    return handleTypeConversion<T>(currentElement, mode);
}

template <typename T>
std::optional<T> jsonValue(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode) {
    std::istringstream jsonStringStream(jsonString);
    _bson::bsonobjbuilder bob;
    _bson::bsonobj obj = fromjson(jsonStringStream, bob);
    return jsonValue<T>(obj, path, mode);
}

// string
template std::optional<std::string> jsonValue<std::string>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
// double
template std::optional<double> jsonValue<double>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<float> jsonValue<float>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
// bool
template std::optional<bool> jsonValue<bool>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
// integers
template std::optional<size_t> jsonValue<size_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<int64_t> jsonValue<int64_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<int32_t> jsonValue<int32_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<uint32_t> jsonValue<uint32_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<int16_t> jsonValue<int16_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<uint16_t> jsonValue<uint16_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<int8_t> jsonValue<int8_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);
template std::optional<uint8_t> jsonValue<uint8_t>(const std::string& jsonString, std::string_view path, ErrorHandlingMode mode);

}  // namespace funcs

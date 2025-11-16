/**
 * @file TestJsonValue.cpp
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 * This file tests the examples presented in the examples folder.
 */

#include <gtest/gtest.h>

#include <string>

#include "bson/json.h"
#include "functions/Exception.h"
#include "functions/JsonValue.h"

using namespace funcs;

TEST(JsonValueTest, MissingPath) {
    std::string s("{y:\"Hello World\"}");
    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.x"), ErrorHandlingMode::ERROR), PathNotFoundError);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, String) {
    std::string s("{y:\"Hello World\"}");
    std::string result = jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value();
    EXPECT_STREQ(result.c_str(), "Hello World");

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, StringNumber) {
    std::string s("{y:\"123.45\"}");
    std::string result = jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value();
    EXPECT_STREQ(result.c_str(), "123.45");

    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<uint64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<int32_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<uint32_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<int16_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<uint16_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<int8_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);
    EXPECT_EQ(jsonValue<uint8_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123);

    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123.45);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 123.45f);

    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, StringBoolean) {
    std::string s("{y:\"true\", x: \"FALSE\"}");
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL).value(), true);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL).value(), false);

    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL).value().c_str(), "true");
    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL).value().c_str(), "FALSE");

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, Integer) {
    std::string s("{y:42}");
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42);

    // check other integral types
    EXPECT_EQ(jsonValue<int32_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42);
    EXPECT_EQ(jsonValue<uint32_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42u);
    EXPECT_EQ(jsonValue<uint16_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42u);
    EXPECT_EQ(jsonValue<int16_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42u);
    EXPECT_EQ(jsonValue<uint8_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42u);
    EXPECT_EQ(jsonValue<int8_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42u);

    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42.0);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value(), 42.0);

    EXPECT_THROW(jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, BooleanTrue) {
    std::string s("{y:true, x: false}");

    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL).value(), true);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL).value(), false);

    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR).value().c_str(), "true");
    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.x"), ErrorHandlingMode::ERROR).value().c_str(), "false");

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.x"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.x"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.y"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.x"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.x"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, ComplexObject) {
    std::string s("{address: {city: \"Heidelberg\"}}");

    EXPECT_THROW(jsonValue<std::string>(s, std::string_view("$.address"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<std::string>(s, std::string_view("$.address"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.address"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.address"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.address"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.address"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.address"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.address"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.address"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.address"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
}

TEST(JsonValueTest, ArrayAccess) {
    std::string s("{address: {cities: [\"Heidelberg\", \"Karachi\", \"Lahore\"]}}");

    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::ERROR).value().c_str(), "Heidelberg");
    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.address.cities[1]"), ErrorHandlingMode::ERROR).value().c_str(), "Karachi");
    EXPECT_STREQ(jsonValue<std::string>(s, std::string_view("$.address.cities[2]"), ErrorHandlingMode::ERROR).value().c_str(), "Lahore");
    EXPECT_THROW(jsonValue<std::string>(s, std::string_view("$.address.cities[3]"), ErrorHandlingMode::ERROR), PathNotFoundError);

    EXPECT_EQ(jsonValue<int64_t>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_EQ(jsonValue<bool>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_EQ(jsonValue<double>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_EQ(jsonValue<float>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::RETURN_NULL), std::nullopt);

    EXPECT_THROW(jsonValue<int64_t>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_THROW(jsonValue<bool>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_THROW(jsonValue<double>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_THROW(jsonValue<float>(s, std::string_view("$.address.cities[0]"), ErrorHandlingMode::ERROR), InvalidTypeConversionError);
}

// AI generated test case
TEST(JsonValueTest, VeryComplexStructure) {
    std::string s(
        "{"
        "  user: {"
        "    name: \"Us\\\"er\","
        "    age: \"27.9\","
        "    active: true,"
        "    address: {"
        "      city: \"CityA\","
        "      zip: 12345,"
        "      history: ["
        "        {year: 2020, city: \"CityB\"},"
        "        {year: \"2021\", city: \"CityC\"},"
        "        {year: 2022.0, city: \"CityD\"}"
        "      ]"
        "    },"
        "    favorites: {"
        "      numbers: [1, \"2\", 3.5, \"4.75\"],"
        "      flags: [true, false, \"true\", \"false\"],"
        "      notes: [null, \"noteA\", {code: \"A1\", valid: false}]"
        "    }"
        "  },"
        "  metadata: {"
        "    version: 1,"
        "    tags: [\"x\", \"y\", \"z\"],"
        "    nested: { level1: { level2: { value: \"123\" } } }"
        "  }"
        "}");

    //
    // Basic string extraction with escape sequences
    //
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.name", ErrorHandlingMode::ERROR)->c_str(), "Us\"er");

    //
    // Numeric string → numeric conversions
    //
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.age", ErrorHandlingMode::ERROR).value(), 27);
    EXPECT_FLOAT_EQ(jsonValue<float>(s, "$.user.age", ErrorHandlingMode::ERROR).value(), 27.9f);
    EXPECT_DOUBLE_EQ(jsonValue<double>(s, "$.user.age", ErrorHandlingMode::ERROR).value(), 27.9);

    //
    // Boolean extraction
    //
    EXPECT_EQ(jsonValue<bool>(s, "$.user.active", ErrorHandlingMode::ERROR).value(), true);
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.active", ErrorHandlingMode::ERROR)->c_str(), "true");

    //
    // Deep object navigation
    //
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.address.city", ErrorHandlingMode::ERROR)->c_str(), "CityA");
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.address.zip", ErrorHandlingMode::ERROR).value(), 12345);

    //
    // Array inside object inside array
    //
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.address.history[1].city", ErrorHandlingMode::ERROR)->c_str(), "CityC");
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.address.history[0].year", ErrorHandlingMode::ERROR).value(), 2020);
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.address.history[1].year", ErrorHandlingMode::ERROR).value(), 2021);
    EXPECT_DOUBLE_EQ(jsonValue<double>(s, "$.user.address.history[2].year", ErrorHandlingMode::ERROR).value(), 2022.0);

    //
    // Non-uniform array types (numbers)
    //
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.favorites.numbers[0]", ErrorHandlingMode::ERROR).value(), 1);
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.favorites.numbers[1]", ErrorHandlingMode::ERROR).value(), 2);
    EXPECT_DOUBLE_EQ(jsonValue<double>(s, "$.user.favorites.numbers[2]", ErrorHandlingMode::ERROR).value(), 3.5);
    EXPECT_DOUBLE_EQ(jsonValue<double>(s, "$.user.favorites.numbers[3]", ErrorHandlingMode::ERROR).value(), 4.75);

    //
    // Mixed boolean-like values
    //
    EXPECT_TRUE(jsonValue<bool>(s, "$.user.favorites.flags[0]", ErrorHandlingMode::ERROR).value());
    EXPECT_FALSE(jsonValue<bool>(s, "$.user.favorites.flags[1]", ErrorHandlingMode::ERROR).value());
    EXPECT_TRUE(jsonValue<bool>(s, "$.user.favorites.flags[2]", ErrorHandlingMode::ERROR).value());
    EXPECT_FALSE(jsonValue<bool>(s, "$.user.favorites.flags[3]", ErrorHandlingMode::ERROR).value());

    // Null handling
    //
    EXPECT_EQ(jsonValue<std::string>(s, "$.user.favorites.notes[0]", ErrorHandlingMode::RETURN_NULL), std::nullopt);
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.favorites.notes[1]", ErrorHandlingMode::ERROR)->c_str(), "noteA");
    EXPECT_STREQ(jsonValue<std::string>(s, "$.user.favorites.notes[2].code", ErrorHandlingMode::ERROR)->c_str(), "A1");
    EXPECT_FALSE(jsonValue<bool>(s, "$.user.favorites.notes[2].valid", ErrorHandlingMode::ERROR).value());

    //
    // Deep nested metadata
    //
    EXPECT_EQ(jsonValue<int64_t>(s, "$.metadata.version", ErrorHandlingMode::ERROR).value(), 1);
    EXPECT_STREQ(jsonValue<std::string>(s, "$.metadata.tags[2]", ErrorHandlingMode::ERROR)->c_str(), "z");
    EXPECT_STREQ(jsonValue<std::string>(s, "$.metadata.nested.level1.level2.value", ErrorHandlingMode::ERROR)->c_str(), "123");

    // Missing path handling
    //
    EXPECT_THROW(jsonValue<int64_t>(s, "$.user.unknown", ErrorHandlingMode::ERROR), PathNotFoundError);
    EXPECT_EQ(jsonValue<int64_t>(s, "$.user.unknown", ErrorHandlingMode::RETURN_NULL), std::nullopt);

    //
    // Type conversion errors
    //
    EXPECT_THROW(jsonValue<bool>(s, "$.user.name", ErrorHandlingMode::ERROR), InvalidTypeConversionError);
    EXPECT_THROW(jsonValue<int64_t>(s, "$.user.address.city", ErrorHandlingMode::ERROR), InvalidTypeConversionError);
}

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

#include "bson/bsonobjbuilder.h"
#include "bson/bsontypes.h"
#include "bson/json.h"
#include "functions/JsonValue.h"

TEST(JsonValueTest, BasicTest) {
    _bson::bsonobjbuilder b;
    std::stringstream s("{x:3,y:\"Hello World\"}");
    _bson::bsonobj o = fromjson(s, b);
    std::string result = funcs::jsonValue<std::string>(o, std::string_view("$.y"));
    EXPECT_STREQ(result.c_str(), "Hello World");
}

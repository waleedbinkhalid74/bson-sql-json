/**
 * @file TestExample.cpp
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
#include "bson/json.h"

TEST(BsonExampleTest, Example1) {
    _bson::bsonobjbuilder b;
    std::stringstream s("{x:3,y:\"hello world\"}");
    _bson::bsonobj o = fromjson(s, b);
    EXPECT_STREQ(o.toString().c_str(), "{ x: 3, y: \"hello world\" }");
}

TEST(BsonExampleTest, Example2) {
    // example of using bsonobjbuilder and of nesting documents
    _bson::bsonobjbuilder b;
    b.append("x", 3.14);
    b.append("y", true);
    _bson::bsonobjbuilder a;
    a.append("x", 2);
    a.append("yy", b.obj());
    _bson::bsonobj o = a.obj();
    EXPECT_STREQ(o.toString().c_str(), "{ x: 2, yy: { x: 3.14, y: true } }");

    // reading value of the "x" field from the bson object
    EXPECT_EQ(o["x"].Int(), 2);

    // "dot notation" example
    EXPECT_EQ(o.getFieldDotted("yy.y").Bool(), true);
}

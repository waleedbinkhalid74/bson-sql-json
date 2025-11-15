/**
 * @file TestPathParser.cpp
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

#include "functions/Exception.h"
#include "functions/parser/PathExpr.h"

TEST(PathParserTest, WithoutRoot) {
    std::string pathString("store");
    EXPECT_THROW(funcs::PathExpr pathExpr(pathString), funcs::ParseError);
}

TEST(PathParserTest, OnlyRoot) {
    std::string pathString("$");
    funcs::PathExpr pathExpr(pathString);
    EXPECT_EQ(pathExpr.getSize(), 1ull);
    EXPECT_STREQ(pathExpr.getToken(0).first.c_str(), "$");
}

TEST(PathParserTest, SimpleFieldAccess) {
    std::string pathString("$.address");
    funcs::PathExpr pathExpr(pathString);
    EXPECT_EQ(pathExpr.getSize(), 2ull);
    EXPECT_STREQ(pathExpr.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr.getToken(1).first.c_str(), "address");
    EXPECT_EQ(pathExpr.getToken(1).second, funcs::PathToken::FIELD);

    std::string pathString2("$.address.street");
    funcs::PathExpr pathExpr2(pathString2);
    EXPECT_EQ(pathExpr2.getSize(), 3ull);
    EXPECT_STREQ(pathExpr2.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr2.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr2.getToken(1).first.c_str(), "address");
    EXPECT_EQ(pathExpr2.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr2.getToken(2).first.c_str(), "street");
    EXPECT_EQ(pathExpr2.getToken(2).second, funcs::PathToken::FIELD);
}

TEST(PathParserTest, SimpleIncorrectFieldAccess) {
    std::string pathString3("$.address..street");
    EXPECT_THROW(funcs::PathExpr pathExpr3(pathString3), funcs::FeatureNotSupportedError);

    std::string pathString4("$.address. street");
    EXPECT_THROW(funcs::PathExpr pathExpr4(pathString4), funcs::ParseError);

    std::string pathString5("$.address .street");
    EXPECT_THROW(funcs::PathExpr pathExpr4(pathString5), funcs::ParseError);

    std::string pathString6("$.address . street");
    EXPECT_THROW(funcs::PathExpr pathExpr4(pathString6), funcs::ParseError);
}

TEST(PathParserTest, InvalidCharactersInUnquotedField) {
    std::string pathString1("$.ad dress");
    EXPECT_THROW(funcs::PathExpr pathExpr1(pathString1), funcs::ParseError);

    std::string pathString2("$.ad[dress]");
    EXPECT_THROW(funcs::PathExpr pathExpr2(pathString2), funcs::ParseError);

    std::string pathString3("$.ad{dress}");
    EXPECT_THROW(funcs::PathExpr pathExpr3(pathString3), funcs::ParseError);

    std::string pathString4("$.ad(dress)");
    EXPECT_THROW(funcs::PathExpr pathExpr4(pathString4), funcs::ParseError);

    std::string pathString5("$.ad:dress");
    EXPECT_THROW(funcs::PathExpr pathExpr5(pathString5), funcs::ParseError);

    // encoded characters
    std::string pathString6("$.ad%20dress");
    EXPECT_THROW(funcs::PathExpr pathExpr6(pathString6), funcs::ParseError);
}

TEST(PathParserTest, SimpleQuotedFieldAccess) {
    std::string pathString("$.\"address\"");
    funcs::PathExpr pathExpr(pathString);
    EXPECT_EQ(pathExpr.getSize(), 2ull);
    EXPECT_STREQ(pathExpr.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr.getToken(1).first.c_str(), "address");
    EXPECT_EQ(pathExpr.getToken(1).second, funcs::PathToken::FIELD);

    std::string pathString2(R"($."address".street)");
    funcs::PathExpr pathExpr2(pathString2);
    EXPECT_EQ(pathExpr2.getSize(), 3ull);
    EXPECT_STREQ(pathExpr2.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr2.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr2.getToken(1).first.c_str(), "address");
    EXPECT_EQ(pathExpr2.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr2.getToken(2).first.c_str(), "street");
    EXPECT_EQ(pathExpr2.getToken(2).second, funcs::PathToken::FIELD);

    std::string pathString3(R"($."address"."street")");
    funcs::PathExpr pathExpr3(pathString3);
    EXPECT_EQ(pathExpr3.getSize(), 3ull);
    EXPECT_STREQ(pathExpr3.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr3.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr3.getToken(1).first.c_str(), "address");
    EXPECT_EQ(pathExpr3.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr3.getToken(2).first.c_str(), "street");
    EXPECT_EQ(pathExpr3.getToken(2).second, funcs::PathToken::FIELD);

    std::string pathString4(R"($."address.street")");
    funcs::PathExpr pathExpr4(pathString4);
    EXPECT_EQ(pathExpr4.getSize(), 2ull);
    EXPECT_STREQ(pathExpr4.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr4.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr4.getToken(1).first.c_str(), "address.street");

    // encoded characters are allowed
    std::string pathString5(R"($."ad%20dress")");
    funcs::PathExpr pathExpr5(pathString5);
    EXPECT_EQ(pathExpr5.getSize(), 2ull);
    EXPECT_STREQ(pathExpr5.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr5.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr5.getToken(1).first.c_str(), "ad%20dress");
    EXPECT_EQ(pathExpr5.getToken(1).second, funcs::PathToken::FIELD);
}

TEST(PathParserTest, EscapedQuotedFields) {
    std::string pathString1(R"($."addre\"ss")");
    funcs::PathExpr pathExpr1(pathString1);
    EXPECT_EQ(pathExpr1.getSize(), 2ull);
    EXPECT_STREQ(pathExpr1.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr1.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr1.getToken(1).first.c_str(), R"(addre\"ss)");
    EXPECT_EQ(pathExpr1.getToken(1).second, funcs::PathToken::FIELD);

    std::string pathString2(R"($."addre\\\"ss")");
    funcs::PathExpr pathExpr2(pathString2);
    EXPECT_EQ(pathExpr2.getSize(), 2ull);
    EXPECT_STREQ(pathExpr2.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr2.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr2.getToken(1).first.c_str(), R"(addre\\\"ss)");
    EXPECT_EQ(pathExpr2.getToken(1).second, funcs::PathToken::FIELD);

    std::string pathString3(R"($."addre\\")");
    funcs::PathExpr pathExpr3(pathString3);
    EXPECT_EQ(pathExpr3.getSize(), 2ull);
    EXPECT_STREQ(pathExpr3.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr3.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr3.getToken(1).first.c_str(), R"(addre\\)");
    EXPECT_EQ(pathExpr3.getToken(1).second, funcs::PathToken::FIELD);

    std::string pathString4(R"($."addre[]")");
    funcs::PathExpr pathExpr4(pathString4);
    EXPECT_EQ(pathExpr4.getSize(), 2ull);
    EXPECT_STREQ(pathExpr4.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr4.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr4.getToken(1).first.c_str(), R"(addre[])");
    EXPECT_EQ(pathExpr4.getToken(1).second, funcs::PathToken::FIELD);

    // empty quoted field
    std::string pathString5(R"($."")");
    funcs::PathExpr pathExpr5(pathString5);
    EXPECT_EQ(pathExpr5.getSize(), 2ull);
    EXPECT_STREQ(pathExpr5.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr5.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr5.getToken(1).first.c_str(), R"()");
    EXPECT_EQ(pathExpr5.getToken(1).second, funcs::PathToken::FIELD);

    // whitespace quoted field
    std::string pathString6(R"($."   ")");
    funcs::PathExpr pathExpr6(pathString6);
    EXPECT_EQ(pathExpr6.getSize(), 2ull);
    EXPECT_STREQ(pathExpr6.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr6.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr6.getToken(1).first.c_str(), R"(   )");
    EXPECT_EQ(pathExpr6.getToken(1).second, funcs::PathToken::FIELD);
}

TEST(PathParserTest, EscapedIncorrectQuotedFields) {
    std::string pathString1(R"($."addre"ss")");
    EXPECT_THROW(funcs::PathExpr pathExpr1(pathString1), funcs::ParseError);

    std::string pathString2(R"($."addre\\"ss")");
    EXPECT_THROW(funcs::PathExpr pathExpr2(pathString2), funcs::ParseError);
}

TEST(PathParserTest, SimpleArrayAccess) {
    std::string pathString("$.store.book[0].title");
    funcs::PathExpr pathExpr(pathString);
    EXPECT_EQ(pathExpr.getSize(), 5ull);
    EXPECT_STREQ(pathExpr.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr.getToken(1).first.c_str(), "store");
    EXPECT_EQ(pathExpr.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr.getToken(2).first.c_str(), "book");
    EXPECT_EQ(pathExpr.getToken(2).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr.getToken(3).first.c_str(), "0");
    EXPECT_EQ(pathExpr.getToken(3).second, funcs::PathToken::ARRAY_INDEX);
    EXPECT_STREQ(pathExpr.getToken(4).first.c_str(), "title");
    EXPECT_EQ(pathExpr.getToken(4).second, funcs::PathToken::FIELD);

    // just array
    std::string pathString2("$[10]");
    funcs::PathExpr pathExpr2(pathString2);
    EXPECT_EQ(pathExpr2.getSize(), 2ull);
    EXPECT_STREQ(pathExpr2.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr2.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr2.getToken(1).first.c_str(), "10");
    EXPECT_EQ(pathExpr2.getToken(1).second, funcs::PathToken::ARRAY_INDEX);

    // array as final field
    std::string pathString3("$.store.book[5]");
    funcs::PathExpr pathExpr3(pathString3);
    EXPECT_EQ(pathExpr3.getSize(), 4ull);
    EXPECT_STREQ(pathExpr3.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr3.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr3.getToken(1).first.c_str(), "store");
    EXPECT_EQ(pathExpr3.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr3.getToken(2).first.c_str(), "book");
    EXPECT_EQ(pathExpr3.getToken(2).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr3.getToken(3).first.c_str(), "5");
    EXPECT_EQ(pathExpr3.getToken(3).second, funcs::PathToken::ARRAY_INDEX);
}

TEST(PathParserTest, IncorrectArrayAccess) {
    std::string pathString1("$.store.book[");
    EXPECT_THROW(funcs::PathExpr pathExpr1(pathString1), funcs::ParseError);

    std::string pathString2("$.store.book]");
    EXPECT_THROW(funcs::PathExpr pathExpr2(pathString2), funcs::ParseError);

    std::string pathString3("$.store.book[abc]");
    EXPECT_THROW(funcs::PathExpr pathExpr3(pathString3), funcs::ParseError);

    std::string pathString4("$.store.book[1.5]");
    EXPECT_THROW(funcs::PathExpr pathExpr3(pathString4), funcs::ParseError);

    std::string pathString5("$.store.book[-5]");
    EXPECT_THROW(funcs::PathExpr pathExpr3(pathString5), funcs::ParseError);

    std::string pathString6("$.store.book[1");
    EXPECT_THROW(funcs::PathExpr pathExpr6(pathString6), funcs::ParseError);

    std::string pathString7("$.store.boo[k1");
    EXPECT_THROW(funcs::PathExpr pathExpr7(pathString7), funcs::ParseError);

    std::string pathString8("$.store.bo]ok1");
    EXPECT_THROW(funcs::PathExpr pathExpr8(pathString8), funcs::ParseError);

    std::string pathString9("$.store.book[]");
    EXPECT_THROW(funcs::PathExpr pathExpr8(pathString9), funcs::ParseError);
}

TEST(PathParserTest, ComplexPath) {
    std::string pathString(R"($."store".book[0]."title.name"[2])");
    funcs::PathExpr pathExpr(pathString);
    EXPECT_EQ(pathExpr.getSize(), 6ull);
    EXPECT_STREQ(pathExpr.getToken(0).first.c_str(), "$");
    EXPECT_EQ(pathExpr.getToken(0).second, funcs::PathToken::ROOT);
    EXPECT_STREQ(pathExpr.getToken(1).first.c_str(), "store");
    EXPECT_EQ(pathExpr.getToken(1).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr.getToken(2).first.c_str(), "book");
    EXPECT_EQ(pathExpr.getToken(2).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr.getToken(3).first.c_str(), "0");
    EXPECT_EQ(pathExpr.getToken(3).second, funcs::PathToken::ARRAY_INDEX);
    EXPECT_STREQ(pathExpr.getToken(4).first.c_str(), "title.name");
    EXPECT_EQ(pathExpr.getToken(4).second, funcs::PathToken::FIELD);
    EXPECT_STREQ(pathExpr.getToken(5).first.c_str(), "2");
    EXPECT_EQ(pathExpr.getToken(5).second, funcs::PathToken::ARRAY_INDEX);
}

TEST(PathParserTest, EmptyPath) {
    std::string pathString("");
    EXPECT_THROW(funcs::PathExpr pathExpr(pathString), funcs::ParseError);
}

TEST(PathParserTest, ObjWildCard) {
    std::string pathString("$.*.city");
    EXPECT_THROW(funcs::PathExpr pathExpr(pathString), funcs::ParseError);
}

TEST(PathParserTest, ArrayWildCard) {
    std::string pathString("$.[*].city");
    EXPECT_THROW(funcs::PathExpr pathExpr(pathString), funcs::ParseError);
}
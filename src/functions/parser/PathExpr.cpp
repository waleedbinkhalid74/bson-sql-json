/**
 * @file PathExpr.cpp
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "functions/parser/PathExpr.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include "functions/Exception.h"

using namespace std::literals;

namespace {
size_t findEndQuote(std::string_view path) {
    const size_t pathLen = path.length();
    for (size_t i = 0; i < pathLen; ++i) {
        if (path[i] == '"') {
            // Count consecutive backslashes before this quote
            size_t backslashes = 0;
            size_t j = i;
            while (j > 0 && path[--j] == '\\') {
                backslashes++;
            }
            if (backslashes % 2 == 0) {
                return i;  // unescaped quote → end
            }
        }
    }
    return std::string_view::npos;
}
}  // namespace

namespace funcs {

PathExpr::PathExpr(std::string_view path) {
    // go over the sql/json path and tokenize it
    if (path.empty() || path[0] != '$') {
        throw ParseError(ParseError::noRootError, 0);
    }

    parsePath(path);

    assert(!m_tokens.empty() && "Path tokens should not be empty after parsing");
}

void PathExpr::parsePath(std::string_view path) {
    const size_t pathLen = path.length();
    // base case
    if (pathLen == 0) {
        return;
    }

    const char* pathChar = path.data();
    switch (*pathChar) {
        case '$':
            m_tokens.emplace_back(std::make_pair<std::string, PathToken>(std::string(path.substr(0, 1)), PathToken::ROOT));
            ++m_currentPos;
            parsePath(path.substr(1));
            break;
        case '.':
            // if next char is also a dot, then throw as decendants are not supported yet
            if (pathLen > 1 && path[1] == '.') {
                throw FeatureNotSupportedError(FeatureNotSupportedError::descendentOperatorError);
            }
            ++m_currentPos;
            parsePath(path.substr(1));
            break;
        case '"': {
            handleQuotedField(path);
            break;
        }
        case '[':
            handleArrayAccess(path);
            break;
        default: {
            handleUnquotedField(path);
            break;
        }
    }
}

void PathExpr::handleQuotedField(std::string_view path) {
    const size_t pathLen = path.length();

    // get the closing quote (unless escaped)
    size_t pos = findEndQuote(path.substr(1));
    if (pos == std::string_view::npos) {
        throw ParseError(ParseError::unexpectedPathExprError, m_currentPos);
    }
    auto identifierName = path.substr(1, pos);
    m_tokens.emplace_back(std::make_pair<std::string, PathToken>(std::string(identifierName), PathToken::FIELD));
    // next character after closing quote must be either dot, array access or end of string
    if (pos + 2 < pathLen && path[pos + 2] != '.' && path[pos + 2] != '[') {
        throw ParseError(ParseError::unexpectedPathExprError, m_currentPos);
    }
    m_currentPos += pos + 2;
    parsePath(path.substr(pos + 2));
}

void PathExpr::handleUnquotedField(std::string_view path) {
    const size_t pathLen = path.length();

    size_t dotPos = path.find_first_of(".");
    size_t bracketPos = path.find_first_of("[");
    size_t pos = 0;
    if (dotPos == std::string_view::npos && bracketPos == std::string_view::npos) {
        pos = pathLen;
    } else if (dotPos > bracketPos && bracketPos != std::string_view::npos) {
        pos = bracketPos;
    } else if (bracketPos > dotPos && dotPos != std::string_view::npos) {
        pos = dotPos;
    }
    auto identifierName = path.substr(0, pos);
    // if the identifier contains spaces or invalid characters, throw parse error
    // if the identifier contains characters other than alphanumerics and underscore, throw parse error
    const bool invalidChar = std::find_if(identifierName.begin(), identifierName.end(),
                                          [](unsigned char c) { return !std::isalnum(c) && c != '_'; }) != identifierName.end();
    if (invalidChar) {
        throw ParseError(ParseError::unexpectedPathExprError, m_currentPos);
    }
    m_tokens.emplace_back(std::make_pair<std::string, PathToken>(std::string(path.substr(0, pos)), PathToken::FIELD));
    m_currentPos += pos;
    parsePath(path.substr(pos));
}

void PathExpr::handleArrayAccess(std::string_view path) {
    const size_t pathLen = path.length();
    if (pathLen < 3) {
        throw ParseError(ParseError::unexpectedPathExprError, m_currentPos);
    }
    assert(path[0] == '[');
    size_t closingBracketPos = path.find(']');
    if (closingBracketPos == std::string_view::npos) {
        m_currentPos += closingBracketPos;
        throw ParseError(ParseError::invalidArrayAccess, m_currentPos);
    }
    auto arrayAccessContent = path.substr(1, closingBracketPos - 1);
    const bool isNumber = !arrayAccessContent.empty() && std::find_if(arrayAccessContent.begin(), arrayAccessContent.end(),
                                                                      [](unsigned char c) { return !std::isdigit(c); }) == arrayAccessContent.end();
    if (!isNumber) {
        m_currentPos += 1;  // position of first character after opening bracket
        throw ParseError(ParseError::invalidArrayAccess, m_currentPos);
    }

    m_tokens.emplace_back(std::make_pair<std::string, PathToken>(std::string(arrayAccessContent), PathToken::ARRAY_INDEX));
    m_currentPos += closingBracketPos + 1;
    parsePath(path.substr(closingBracketPos + 1));
}
}  // namespace funcs
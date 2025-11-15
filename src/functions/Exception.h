/**
 * @file Exception.h
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <exception>
#include <string>
namespace funcs {
/**
 * @brief Exception class for parse errors of the SQL/JSON path expression
 *
 */
class ParseError : public std::exception {
   public:
    explicit ParseError(std::string msg, size_t pos) : m_message(" Error at position " + std::to_string(pos) + ": " + std::move(msg)) {
    }

    const char* what() const noexcept override {
        return m_message.c_str();
    }

    static constexpr const char* noRootError = "Path must start with root token '$'";
    static constexpr const char* unexpectedPathExprError = "Unexpected path expression. Please check the syntax as per SQL/JSON standard.";
    static constexpr const char* invalidArrayAccess = "Invalid array access expression.";

   private:
    std::string m_message;
};

class FeatureNotSupportedError : public std::exception {
   public:
    explicit FeatureNotSupportedError(std::string msg) : m_message(std::move(msg)) {
    }

    const char* what() const noexcept override {
        return m_message.c_str();
    }

    static constexpr const char* descendentOperatorError = "Descendant operator '..' is not supported yet.";

   private:
    std::string m_message;
};
}  // namespace funcs

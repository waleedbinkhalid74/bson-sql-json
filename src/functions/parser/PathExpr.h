/**
 * @file PathExpr.h
 * @author Waleed Bin Khalid (waleed.binkhalid@hotmail.com)
 * @brief parses the json access path as per SQL/JSON standard
 * @version 0.1
 * @date 2025-11-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace funcs {

enum PathToken {
    ROOT,            // $
    FIELD,           // .fieldName
    ARRAY_INDEX,     // [index]
    WILDCARD_FIELD,  // .*
    WILDCARD_ARRAY   // [*]
};

class PathExpr {
    using TokenPair_t = std::pair<std::string, PathToken>;
    using TokenPairs_t = std::vector<TokenPair_t>;

   public:
    /**
     * @brief Construct a new Path Parser object
     *
     * @param path the json path to parse as per SQL/JSON standard (see
     * https://docs.oracle.com/en/database/oracle/oracle-database/21/adjsn/json-path-expressions.html#GUID-AEBAD813-99AB-418A-93AB-F96BC1658618)
     */
    PathExpr(std::string_view path);

    /**
     * @brief Get the Size of the parsed path
     *
     * @return size_t
     */
    inline size_t getSize() const {
        return m_tokens.size();
    }

    /**
     * @brief Get the Token object at index idx
     *
     * @param idx
     * @return const TokenPair_t& token string and type
     */
    inline const TokenPair_t& getToken(size_t idx) const {
        return m_tokens[idx];
    }

   private:
    void parsePath(std::string_view path);
    void handleQuotedField(std::string_view path);
    void handleUnquotedField(std::string_view path);
    void handleArrayAccess(std::string_view path);

    TokenPairs_t m_tokens;
    size_t m_currentPos{0};
};
}  // namespace funcs

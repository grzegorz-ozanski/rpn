#pragma once

#include <algorithm>
#include <istream>
#include <string>
#include "constant.hpp"
class Token {
    std::string token;
    static bool is_constant(const std::string& token);
public:
    Token() = default;
    Token(const std::string& token) : token(token) {}
    friend std::istream& operator>>(std::istream& in, Token& token) {
        return in >> token.token;
    }
    const std::string& get_token() const { return token; }
    operator std::string() const { return token; }
    bool is_constant() const;
    bool is_number() const;
	bool is_command() const;
    double to_number() const;
};

inline std::string operator+(const char* lhs, const Token& rhs) {
    return std::string(lhs) + static_cast<std::string>(rhs);
}

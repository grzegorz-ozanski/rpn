#pragma once

#include <istream>
#include <string>

namespace rpn {
    class Token {
    public:
        enum Type {
            NUMBER,       // Numeric value
            COMMAND,      // Command (e.g., "add", "sub", etc.)
            OPERATOR,     // Operator (e.g., "+", "-", "*", "/")
            UNKNOWN       // Unknown token type
        };

    private:
        std::string token;
        static bool is_constant(const std::string& token);
        bool is_number() const;
        bool is_command() const;
        bool is_operator() const;
    public:
        Token() = default;
        Token(const std::string& token) : token(token) {}
        friend std::istream& operator>>(std::istream& in, Token& token) {
            return in >> token.token;
        }
        const std::string& get_token() const { return token; }
        operator std::string() const { return token; }
        double to_number() const;
        operator double() const { return to_number(); }
        Type type() const {
            if (is_operator()) return OPERATOR;
            if (is_number()) return NUMBER;
            if (is_command()) return COMMAND;
            return UNKNOWN;
        }
    };

    inline std::string operator+(const char* lhs, const Token& rhs) {
        return std::string(lhs) + static_cast<std::string>(rhs);
    }
}
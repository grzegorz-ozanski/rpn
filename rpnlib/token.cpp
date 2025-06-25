#include <optional>

#include "token.hpp"
#include "command.hpp"
#include "constant.hpp"
#include "operator.hpp"

namespace rpn {
    bool Token::is_constant(const std::string& token) {
        return ReqisteredConstants::contains(token);
    }

    bool Token::is_operator() const {
        return ReqisteredOperators::contains(token);
    }

    bool Token::is_command() const {
        return token.starts_with(":");
    }

    bool Token::is_number() const {
        if (token.empty()) return false;
        if (is_constant(token) || token[0] == '-' && is_constant(token.substr(1))) return true; // Check if it's a constant
        std::size_t pos = 0;
        try {
            auto unused_value = std::stod(token, &pos);
        }
        catch (...) { }
        return pos == token.size(); // Must be processed completely
    }

    double Token::to_number() const {
        auto find_constant_value = [](const std::string& name) -> std::optional<double> {
            for (const auto& entry : ReqisteredConstants::all) {
                if (entry.name == name)
                    return entry.value;
            }
            return std::nullopt;
            };

        if (auto val = find_constant_value(token)) {
            return *val;
        }

        if (token[0] == '-') {
            std::string inner = token.substr(1);
            if (auto val = find_constant_value(inner)) {
                return -(*val);
            }
        }

        return std::stod(token);
    }
}
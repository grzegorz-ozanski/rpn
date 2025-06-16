#include <optional>

#include "token.hpp"
#include "command.hpp"
#include "constant.hpp"
#include "operator.hpp"

bool Token::is_constant(const std::string& token) {
    return ReqisteredConstants::contains(token);
}

bool Token::is_operator() const {
	return ReqisteredOperators::contains(token);
}

bool Token::is_constant() const {
	return is_constant(token);
}

bool Token::is_command() const {
    return token.starts_with(":");
}

bool Token::is_number() const {
    if (token.empty()) return false;
    if (is_constant(token) || token[0] == '-' && is_constant(token.substr(1))) return true; // Check if it's a constant
    if (token.size() > 1 && token[0] == '-' && std::isdigit(token[1])) {
        return std::all_of(token.begin() + 1, token.end(), ::isdigit);
    }
    return std::all_of(token.begin(), token.end(), ::isdigit);
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


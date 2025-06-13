#include "token.hpp"
#include "command.hpp"

bool Token::is_constant(const std::string& token) {
    return const_map.find(token) != const_map.end();
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
    if (is_constant(token)) {
        return std::get<0>(const_map.at(token));
    }
    if (token[0] == '-' && is_constant(token.substr(1))) {
        return -std::get<0>(const_map.at(token.substr(1)));
    }
    return std::stod(token);
}


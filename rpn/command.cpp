#include <format>
#include <iomanip>
#include <iostream>
#include "command.hpp"
#include "operator.hpp"
#include "constant.hpp"
#include "vecutils.hpp"
template <typename Container, typename InfoFunc>
void print_aligned(std::ostream& out, const std::string& header, const Container& items, InfoFunc get_info) {
    size_t max_len = 0;
    for (const auto& item : items)
        max_len = std::max(max_len, vecutils::get_key(item).size());

    int padding = static_cast<int>(max_len) + 2;

	out << "\nAvailable " << header << ":\n";
    for (const auto& item : items) {
        out << std::left << std::setw(padding)
            << (vecutils::get_key(item) + ": ") << get_info(item) << "\n";
    }
}

Command::Command(const Token& token) : token(token) {
	auto it = vecutils::find_in_vector(cmd_map, token.get_token());
    if (it != cmd_map.end()) {
        cmdcode = std::get<1>(*it);
    }
    else {
        throw std::runtime_error("Unknown command: " + token.get_token());
    }
}
void Command::help(std::ostream& out) {
    print_aligned(out, "operators", op_map,
        [](const auto& item) {
            const auto& [name, code, info, operands] = item;
            return info + " (requires " + std::to_string(operands) +
                " operand" + (operands > 1 ? "s" : "") + ")";
        });
    print_aligned(out, "constants", const_map,
        [](const auto& item) {
            const auto& [name, value, info] = item;
            return info + " (value: " + std::format("{:.5f}", value) + ")";
        });
    print_aligned(out, "commands", cmd_map,
        [](const auto& item) {
            const auto& [name, code, info] = item;
            return info;
        });
    out << "\nEnter expression or '" << Command::find_name(Command::CMD_EXIT) << "' to quit.\n";
}

std::string Command::find_name(const CmdCode& cmdcode) {
    for (const auto& [name, code, info] : cmd_map) {
        if (code == cmdcode)
            return name;
    }
    throw std::runtime_error("Command not found");
}

bool Command::execute(std::ostream& out) const {
    switch (cmdcode) {
    case CMD_HELP: 
        help(out);
        break;
    case CMD_EXIT:
		return false; // Indicate exit
    default: 
        throw std::runtime_error("Unknown command code: " + std::to_string(cmdcode));
    }
    return true;
}

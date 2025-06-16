#include <iomanip>
#include <iostream>
#include "command.hpp"
#include "operator.hpp"
#include "constant.hpp"
#include "vecutils.hpp"


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
    int padding = static_cast<int>(vecutils::max_len(op_map)) + 2;
    out << "\nAvailable operators:\n";
    for (const auto& [op, code, info, operands] : op_map) {
        out << std::left << std::setw(padding) << (op + ": ") << info << " (requires " << operands << " operand" << (operands > 1 ? "s" : "") << ")\n";
    }
    padding = static_cast<int>(vecutils::max_len(const_map)) + 2;
    out << "\nAvailable constants:\n";
    for (const auto& [name, value, info] : const_map) {
        out << std::left << std::setw(padding) << (name + ": ") << info << " (value: " << value << ")\n";
    }
    padding = static_cast<int>(vecutils::max_len(cmd_map)) + 2;
    out << "\nAvailable commands:\n";
    for (const auto& [name, code, info] : cmd_map) {
        out << std::left << std::setw(padding) << (name + ": ") << info << "\n";
    }
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

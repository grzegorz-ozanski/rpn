#include <iomanip>
#include <iostream>
#include "command.hpp"
#include "operator.hpp"
#include "constant.hpp"
#include "vecutils.hpp"
template <typename Container>
void print_aligned(std::ostream& out, const std::string& header, const Container& items) {
    size_t max_len = 0;
    for (const auto& item : items)
        max_len = std::max(max_len, vecutils::get_key(item).size());

    int padding = static_cast<int>(max_len) + 2;

	out << "\nAvailable " << header << ":\n";
    for (const auto& item : items) {
        out << std::left << std::setw(padding)
            << (vecutils::get_key(item) + ": ") << vecutils::get_info(item) << "\n";
    }
}

Command::Command(const Token& token) : token(token) {
    auto it = ReqisteredCommands::find(token);
    if (it) {
        cmdcode = it->code;
    }
    else {
        throw std::runtime_error("Unknown command: " + token.get_token());
    }
}
void Command::help(std::ostream& out) {
    print_aligned(out, "operators", ReqisteredOperators::all);
    print_aligned(out, "constants", ReqisteredConstants::all);
    print_aligned(out, "commands", ReqisteredCommands::all);
    out << "\nEnter expression or '" << Command::find_name(Command::CMD_EXIT) << "' to quit.\n";
}

std::string Command::find_name(const CmdCode& cmdcode) {
    for (const auto& item: ReqisteredCommands::all) {
        if (item.code == cmdcode)
            return item.name;
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

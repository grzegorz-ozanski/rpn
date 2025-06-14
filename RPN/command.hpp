#pragma once

#include <string>
#include <tuple>
#include <vector>
#include "token.hpp"

class Command {
public:
    enum CmdCode {
        CMD_HELP = 0,
        CMD_EXIT,
        CMD_NONE
    };

private:
    const Token& token;
    CmdCode cmdcode; // Operator symbol

public:
    Command(const Token& token);

    static void help(std::ostream& out, bool printStatusMessage = true);
    
    static std::string find_name(const CmdCode& code);

    bool execute(std::ostream& out) const;
    bool operator()(std::ostream& out) const {
		return execute(out);
	}
};

const std::vector<std::tuple<std::string, Command::CmdCode, std::string>> cmd_map = {
    {":help", Command::CMD_HELP, "print help message"},
    {":exit", Command::CMD_EXIT, "exit"},
};


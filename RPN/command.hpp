#pragma once

#include <string>
#include <tuple>
#include <vector>
#include "token.hpp"
#include "info.hpp"
#include "vecutils.hpp"

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

    static std::string find_name(const CmdCode& code);

public:
    Command(const Token& token);

    static void help(std::ostream& out);
    
    bool execute(std::ostream& out) const;
    bool operator()(std::ostream& out) const {
		return execute(out);
	}
};

class CommandInfo : public BaseInfo {
public:
    Command::CmdCode code;

    CommandInfo(const std::string& name, Command::CmdCode code, const std::string& info)
        : BaseInfo(name, info), code(code) {
    }
};

class ReqisteredCommands {
public:
    inline static const std::vector<CommandInfo> all = {
        {":help", Command::CMD_HELP, "print help message"},
        {":exit", Command::CMD_EXIT, "exit"},
    };

    static const CommandInfo* find(const Token& token) {
        auto it = vecutils::find_in_vector(all, token.get_token());
        return it != all.end() ? &(*it) : nullptr;
    }
};

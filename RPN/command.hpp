#pragma once

#include <string>
#include <vector>
#include "token.hpp"
#include "entry.hpp"

namespace rpn {
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

    class CommandInfo : public EntryInfo {
    public:
        Command::CmdCode code;

        CommandInfo(const std::string& name, Command::CmdCode code, const std::string& info)
            : EntryInfo(name, info), code(code) {
        }
    };

    template <>
    inline const std::vector<CommandInfo> EntryRegistry<CommandInfo>::all = {
        {":help", Command::CMD_HELP, "print help message"},
        {":exit", Command::CMD_EXIT, "exit"},
    };

    using ReqisteredCommands = EntryRegistry<CommandInfo>;
}
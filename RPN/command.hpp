#pragma once

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include "token.hpp"
#include "operator.hpp"
#include "constant.hpp"

enum CmdCode {
    CMD_HELP = 0,
    CMD_EXIT,
};

const std::map<std::string, std::tuple<CmdCode, std::string>> cmd_map = {
    {":help",    std::make_tuple(CMD_HELP, "print help message")},
    {":exit",    std::make_tuple(CMD_EXIT, "exit")},
};

class Command {
    const Token& token;
    CmdCode cmdcode; // Operator symbol

public:
    Command(const Token& token) : token(token) {
        auto it = cmd_map.find(token.get_token());
        if (it != cmd_map.end()) {
            cmdcode = std::get<0>(it->second);
        }
        else {
            throw std::runtime_error("Unknown command: " + token.get_token());
        }
    }
    static void help(bool printStatusMessage = true) {
        std::cout << "\nAvailable operators:\n";
        for (const auto& [op, info] : op_map) {
            auto operands = std::get<2>(info);
            std::cout << op << ": " << std::get<1>(info) << " (requires " << operands << " operand" << (operands > 1 ? "s" : "") << ")\n";
        }
        std::cout << "\nAvailable constants:\n";
        for (const auto& [constant, info] : const_map) {
            std::cout << constant << ": " << std::get<1>(info) << " (value: " << std::get<0>(info) << ")\n";
        }
        std::cout << "\nAvailable commands:\n";
        for (const auto& [constant, info] : cmd_map) {
            std::cout << constant << ": " << std::get<1>(info) << "\n";
        }
        if (printStatusMessage)
            std::cout << "Enter '" << find_name(CMD_EXIT)  << "' to quit.\n";
    }
    static std::string find_name(const CmdCode &code) {
        for (const auto& [name, info] : cmd_map) {
            if (std::get<0>(info) == code)
                return name;
        }
        throw std::runtime_error("Command not found");
    }

    bool execute() const {
        switch (cmdcode) {
        case CMD_HELP: help(); break;
		case CMD_EXIT: return false;
        default: throw std::runtime_error("Unknown command code: " + std::to_string(cmdcode));
        }
		return true;
    }

};
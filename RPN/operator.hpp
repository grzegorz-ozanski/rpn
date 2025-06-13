#pragma once

#include <map>
#include <stack>
#include <string>
#include <tuple>
#include "token.hpp"

enum OpCode {
    OP_ADD = 0,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_POWER,
    OP_NEGATE,
    OP_ABS,
    OP_LOG10,
    OP_LN,
    OP_LOGB
};

const std::map<std::string, std::tuple<OpCode, std::string, int>> op_map = {
    {"+",    std::make_tuple(OP_ADD, "addition", 2)},
    {"-",    std::make_tuple(OP_SUBTRACT, "subtraction", 2)},
    {"*",    std::make_tuple(OP_MULTIPLY, "multiplication", 2)},
    {"/",    std::make_tuple(OP_DIVIDE, "division", 2)},
    {"^",    std::make_tuple(OP_POWER, "power", 2)},
    {"**",   std::make_tuple(OP_POWER, "power (alias)", 2)},
    {"neg",  std::make_tuple(OP_NEGATE, "negation", 1)},
    {"abs",  std::make_tuple(OP_ABS, "absolute value", 1)},
    {"log",  std::make_tuple(OP_LOG10,  "base 10 logarithm", 1)},
    {"ln",   std::make_tuple(OP_LN, "natural logarithm", 1)},
    {"logn", std::make_tuple(OP_LOGB, "logarithm with base n", 2)}
};

class Operator {
    const Token &token; // Operator symbol as string
    OpCode opcode; // Operator symbol
    int operands; // Number of operands required

    std::tuple<double, double> pop_operands(std::stack<double>& stack) const;

public:
    Operator(const Token& token);

    double apply(std::stack<double>& stack) const;

    double operator ()(std::stack<double>& stack) const {
		return apply(stack);
    }
};

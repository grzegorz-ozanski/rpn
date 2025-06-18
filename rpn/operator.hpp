#pragma once

#include <stack>
#include <string>
#include <vector>
#include "token.hpp"
#include "entry.hpp"

namespace rpn {
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

    class Operator {
        const Token& token; // Operator symbol as string
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

    class OperatorInfo : public EntryInfo {
    public:
        OpCode code;
        int operands;
        OperatorInfo(const std::string& name, OpCode code, const std::string& info, int operands)
            : EntryInfo(name, info), code(code), operands(operands) {
        }

        virtual std::string get_info() const {
            return info + " (requires " + std::to_string(operands) +
                " operand" + (operands > 1 ? "s" : "") + ")";
        }

    };

    template <>
    inline const std::vector<OperatorInfo> EntryRegistry<OperatorInfo>::all = {
        {"+", OP_ADD, "addition", 2},
        {"-", OP_SUBTRACT, "subtraction", 2},
        {"*", OP_MULTIPLY, "multiplication", 2},
        {"/", OP_DIVIDE, "division", 2},
        {"^", OP_POWER, "power", 2},
        {"**", OP_POWER, "power (alias)", 2},
        {"neg", OP_NEGATE, "negation", 1},
        {"abs", OP_ABS, "absolute value", 1},
        {"log", OP_LOG10, "base 10 logarithm", 1},
        {"ln", OP_LN, "natural logarithm", 1},
        {"logn", OP_LOGB, "logarithm with base n", 2}
    };

    using ReqisteredOperators = EntryRegistry<OperatorInfo>;
}
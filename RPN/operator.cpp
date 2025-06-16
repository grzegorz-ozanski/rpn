#include <cmath>
#include <stdexcept>
#include "operator.hpp"

Operator::Operator(const Token& token) : token(token) {
    auto it = ReqisteredOperators::find(token);
    if (!it) {
        throw std::runtime_error("Unknown operator: " + token);
    }
    opcode = it->code;
    operands = it->operands;
}


std::tuple<double, double> Operator::pop_operands(std::stack<double>& stack) const {
    if (stack.size() < operands) throw std::runtime_error("Too few operands");
    double a, b;
    switch (operands) {
    case 1:
        a = stack.top(); stack.pop();
        b = 0; // For unary operators, we can ignore b
        break;
    case 2:
        b = stack.top(); stack.pop();
        a = stack.top(); stack.pop();
        break;
    default:
        throw std::runtime_error("Invalid number of operands for operator: " + token);
    }
    return std::make_tuple(a, b);
}

double Operator::apply(std::stack<double>& stack) const {
    auto [a, b] = pop_operands(stack);
    switch (opcode) {
    case OP_ADD: return a + b;
    case OP_SUBTRACT: return a - b;
    case OP_MULTIPLY: return a * b;
    case OP_DIVIDE:
        if (b == 0.0) throw std::runtime_error("Division by zero");
        return a / b;
    case OP_NEGATE: return a != 0 ? -a : a;
    case OP_POWER:
        if (a < 0 && b != static_cast<int>(b))
            throw std::runtime_error("Negative base with non-integer exponent");
        return std::pow(a, b);
    case OP_ABS: return std::abs(a);
    case OP_LOG10:
        if (a <= 0) throw std::runtime_error("Logarithm domain error");
        return std::log10(a);
    case OP_LN:
        if (a <= 0) throw std::runtime_error("Logarithm domain error");
        return std::log(a);
    case OP_LOGB:
        if (a <= 0 || b <= 0 || b == 1) throw std::runtime_error("Logarithm domain error");
        return std::log(a) / std::log(b);
    default: throw std::runtime_error("Unknown operator code");
    }
}

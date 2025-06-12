#include "RPN.h"

enum OpCode {
    OP_ADD = 0,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_ABS
};

struct Operator {
    const std::string token; // Operator symbol as string
	OpCode opcode; // Operator symbol
	int operands; // Number of operands required
	Operator(const std::string& o): token(o) {
        if (o == "+") opcode = OP_ADD;
        else if (o == "-") opcode = OP_SUBTRACT;
        else if (o == "*") opcode = OP_MULTIPLY;
        else if (o == "/") opcode = OP_DIVIDE;
        else if (o == "neg") opcode = OP_NEGATE;
        else if (o == "abs") opcode = OP_ABS;
		else throw std::runtime_error("Unknown operator: " + o);
		operands = (opcode == OP_NEGATE || opcode == OP_ABS) ? 1 : 2; // Unary operators have 1 operand, others have 2
    }


    std::tuple<double, double> pop_operands(std::stack<double>& stack) const {
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

    double apply(std::stack<double> &stack) const {
		auto [a, b] = pop_operands(stack);
        switch (opcode) {
            case OP_ADD: return a + b;
            case OP_SUBTRACT: return a - b;
            case OP_MULTIPLY: return a * b;
            case OP_DIVIDE:
                if (b == 0.0) throw std::runtime_error("Division by zero");
                return a / b;
            case OP_NEGATE: return a != 0 ? -a: a;
            case OP_ABS: return std::abs(a);
            default: throw std::runtime_error("Unknown operator code");
        }
    }
};

Operator operators[] = {
    {"+"},
    {"-"},
    {"*"},
    {"/"},
    {"neg"}, // Unary operator
    {"abs"} // Unary operator
};

int main() {
    std::string line;
    std::cout << "RPN Calculator. Enter expression or 'exit':\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") break;

        std::stack<double> stack;
        std::istringstream iss(line);
        std::string token;

        try {
            while (iss >> token) {
                if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
                    stack.push(std::stod(token));
                }
                else {
                    stack.push(Operator(token).apply(stack));
                }
            }

            if (stack.size() != 1) throw std::runtime_error("Invalid expression");
            std::cout << "Result: " << stack.top() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

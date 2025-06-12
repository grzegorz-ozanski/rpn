#include "RPN.h"

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
    {"logb", std::make_tuple(OP_LOGB, "logarithm with base b", 2)}
};

const std::map<std::string, std::tuple<double, std::string>> const_map = {
    {"pi", std::make_tuple(std::numbers::pi, "π")},
    {"e",  std::make_tuple(std::numbers::e, "e (Euler's constant)") }
};

struct Operator {
    const std::string token; // Operator symbol as string
	OpCode opcode; // Operator symbol
	int operands; // Number of operands required
	Operator(const std::string& o): token(o) {
		auto it = op_map.find(o);
        if (it == op_map.end()) {
            throw std::runtime_error("Unknown operator: " + o);
		}
		opcode = std::get<0>(it->second);
		operands = std::get<2>(it->second);
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
};

bool is_constant(const std::string& token) {
    return const_map.find(token) != const_map.end();
}

bool is_number(const std::string& token) {
    if (token.empty()) return false;
	if (is_constant(token) || token[0] == '-' && is_constant(token.substr(1))) return true; // Check if it's a constant
    if (token.size() > 1 && token[0] == '-' && std::isdigit(token[1])) {
        return std::all_of(token.begin() + 1, token.end(), ::isdigit);
    }
    return std::all_of(token.begin(), token.end(), ::isdigit);
}

double to_number(const std::string& token) {
    if (is_constant(token)) {
        return std::get<0>(const_map.at(token));
    }
    if (token[0] == '-' && is_constant(token.substr(1))) {
        return -std::get<0>(const_map.at(token.substr(1)));
    }
    return std::stod(token);
}

void help(bool printStatusMessage = true) {
    std::cout << "Available operators:\n";
    for (const auto& [op, info] : op_map) {
        auto operands = std::get<2>(info);
        std::cout << op << ": " << std::get<1>(info) << " (requires " << operands << " operand" << (operands > 1 ? "s": "") << ")\n";
	}
    std::cout << "Available constants:\n";
    for (const auto& [constant, info] : const_map) {
		std::cout << constant << ": " << std::get<1>(info) << " (value: " << std::get<0>(info) << ")\n";
    }
    if (printStatusMessage)
        std::cout << "Enter 'exit' to quit.\n";
}

int main() {
    std::string line;
    std::cout << "RPN Calculator.\n";
	help(false); // Print help without status message
    std::cout << "Enter expression or 'exit':\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") break;

        std::stack<double> stack;
        std::istringstream iss(line);
        std::string token;

        try {
			bool help_parsed = false; // Reset help flag for each new line
            while (iss >> token) {
                if (token == "help") {
                    help();
					help_parsed = true; // Set help flag to true
                    continue;
				}
                if (is_number(token)) {
                    stack.push(to_number(token));
                }
                else {
                    stack.push(Operator(token).apply(stack));
                }
            }

			if (help_parsed) continue; // Skip result output if help was requested
            if (stack.size() != 1) throw std::runtime_error("Invalid expression");
            std::cout << "Result: " << stack.top() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

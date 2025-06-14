#include <optional>
#include <sstream>
#include "rpn.hpp"


namespace rpn {
    bool run(std::istream& in, std::ostream& out, std::ostream& err)
    {
        std::string line;
        out << prompt;
        if (!std::getline(in, line)) return false;
        std::stack<double> stack;
        std::istringstream iss(line);
        std::optional<Command> command;

        try {
            if (line.find_first_not_of(" \t\n\r") == std::string::npos) {
                throw std::runtime_error("No input provided");
            }
            Token token;
            while (!command.has_value() && iss >> token) {
                switch (token.type()) {
                case Token::COMMAND:
                    command.emplace(token);
                    continue;
                case Token::NUMBER:
                    stack.push(token);
                    break; // Valid number, proceed
                case Token::OPERATOR:
                    stack.push(Operator(token)(stack));
                    break; // Valid operator, proceed
                default:
                    throw std::runtime_error("Invalid token");
                }
            }

            if (command.has_value()) {
                if (!command->execute(out)) {
                    out << "Exiting calculator.\n";
                    return false;
                }
                return true; // Continue running
            }
            if (stack.size() != 1) throw std::runtime_error("Invalid expression");
            out << "Result: " << stack.top() << "\n";
        }
        catch (const std::exception& e) {
            err << "Error: " << e.what() << "\n";
        }
        return true; // Continue running
    }
}
#include "command.hpp"
#include "RPN.hpp"
#include "operator.hpp"
#include "token.hpp"
#include "utf_console.hpp"


int main() {
    set_utf8_console();
    std::string line;
    std::cout << "RPN Calculator.\n";
	Command::help(false); // Print help without status message
    std::cout << "\nEnter expression or '" << Command::find_name(CMD_EXIT) << "':\n";

    while (true) {
        bool should_continue = true; // Flag to control loop continuation
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::stack<double> stack;
        std::istringstream iss(line);
        std::string token;

        try {
			bool command_executed = false; // Reset help flag for each new line
            Token token;
            while (iss >> token) {
                if (token.is_command()) {
                    should_continue = Command(token).execute();
					command_executed = true; // Set help flag to true
                    continue;
				}
                if (token.is_number()) {
                    stack.push(token.to_number());
                }
                else {
                    stack.push(Operator(token)(stack));
                }
            }

			if (!should_continue) break; // Exit or help command was executed
			if (command_executed) continue; // Skip result output if help was requested
            if (stack.size() != 1) throw std::runtime_error("Invalid expression");
            std::cout << "Result: " << stack.top() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

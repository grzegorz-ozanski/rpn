#include "rpn.hpp"
#include "utf_console.hpp"

int main() {
    set_utf8_console();

    std::cout << "RPN Calculator.\n";
    Command::help(std::cout, false); // Print help without status message
    std::cout << "\nEnter expression or '" << Command::find_name(Command::CMD_EXIT) << "':\n";

    while (rpn::run(std::cin, std::cout, std::cerr));
    return 0;
}

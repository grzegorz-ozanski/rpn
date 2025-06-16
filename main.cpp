#include "rpn.hpp"
#include "utf_console.hpp"

int main() {
    set_utf8_console();

    std::cout << "RPN Calculator.\n";
    rpn::Command::help(std::cout);

    while (rpn::run(std::cin, std::cout, std::cerr));
    return 0;
}

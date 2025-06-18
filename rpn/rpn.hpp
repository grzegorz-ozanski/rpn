#pragma once

#include <string>
#include <iostream>
#include "command.hpp"
#include "operator.hpp"
#include "token.hpp"

namespace rpn {
	const std::string prompt = "> ";

	bool run(std::istream& in, std::ostream& out, std::ostream& err);
}

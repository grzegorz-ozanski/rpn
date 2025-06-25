#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <streambuf>
#include <stack>
#include "rpn.hpp"
inline bool run_test(const std::string& input, const std::string& output, const bool result = true) {
    std::stringstream in(input + "\n");
    std::stringstream out;
    std::stringstream err;

    bool run_result = rpn::run(in, out, err);
    return
        ((output.find("Error") != std::string::npos ? "" : rpn::prompt) + output + "\n" == (err.str().empty() ? out.str() : err.str())) &&
        run_result == result;
}

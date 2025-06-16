// tests/test_rpn.cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <streambuf>
#include <stack>
#include "rpn.hpp"

bool run_test(const std::string& input, const std::string& output, const bool result=true) {
    std::stringstream in(input + "\n");
    std::stringstream out;
    std::stringstream err;

    bool run_result = rpn::run(in, out, err);
    return 
        ((output.find("Error") != std::string::npos ? "" : rpn::prompt) + output + "\n" == (err.str().empty() ? out.str() : err.str())) &&
        run_result == result;
}

TEST_CASE("Tests.Simple.SimpleArithmetic") {
    REQUIRE(run_test("3 4 +", "Result: 7"));
    REQUIRE(run_test("10 2 /", "Result: 5"));
    REQUIRE(run_test("5 3 -", "Result: 2"));
    REQUIRE(run_test("6 7 *", "Result: 42"));
}

TEST_CASE("Tests.Simple.ComplexExpressions") {
    REQUIRE(run_test("2 3 + 4 *", "Result: 20"));
    REQUIRE(run_test("5 1 2 + 4 * + 3 -", "Result: 14"));
}

TEST_CASE("Tests.Simple.Errors") {
    REQUIRE(run_test("", "Error: No input provided"));
    REQUIRE(run_test("3 +", "Error: Too few operands"));
    REQUIRE(run_test("3 2 1 +", "Error: Invalid expression"));
    REQUIRE(run_test("4 0 /", "Error: Division by zero"));
    REQUIRE(run_test("xyz", "Error: Invalid token"));
}

TEST_CASE("Tests.Simple.Constants") {
    REQUIRE(run_test("pi", "Result: 3.14159"));
    REQUIRE(run_test("-pi", "Result: -3.14159"));
    REQUIRE(run_test("e", "Result: 2.71828"));
}

TEST_CASE("Tests.Simple.Commands") {
    REQUIRE(run_test(":quit", "Error: Unknown command: :quit"));
    REQUIRE(run_test(":help", R"EOF(
Available operators:
+:    addition (requires 2 operands)
-:    subtraction (requires 2 operands)
*:    multiplication (requires 2 operands)
/:    division (requires 2 operands)
^:    power (requires 2 operands)
**:   power (alias) (requires 2 operands)
neg:  negation (requires 1 operand)
abs:  absolute value (requires 1 operand)
log:  base 10 logarithm (requires 1 operand)
ln:   natural logarithm (requires 1 operand)
logn: logarithm with base n (requires 2 operands)

Available constants:
pi: π (value: 3.14159)
e:  e (Euler's constant) (value: 2.71828)

Available commands:
:help: print help message
:exit: exit

Enter expression or ':exit' to quit.)EOF"));
    REQUIRE(run_test(":exit", "Exiting calculator.", false));
}

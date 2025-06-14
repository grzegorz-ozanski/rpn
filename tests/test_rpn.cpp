// tests/test_rpn.cpp
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <streambuf>
#include <stack>
#include "rpn.hpp"

bool run_test(const std::string& input, const std::string& output) {
    std::stringstream in(input + "\n");
    std::stringstream out;
    std::stringstream err;

    rpn::run(in, out, err);
    return (output.find("Error") != std::string::npos ? "" : rpn::prompt) + output + "\n" == (err.str().empty() ? out.str() : err.str());
}

TEST_CASE("Arithmetic.Simple") {
    REQUIRE(run_test("3 4 +", "Result: 7"));
    REQUIRE(run_test("10 2 /", "Result: 5"));
    REQUIRE(run_test("5 3 -", "Result: 2"));
    REQUIRE(run_test("6 7 *", "Result: 42"));
}

TEST_CASE("Expressions.Complex") {
    REQUIRE(run_test("2 3 + 4 *", "Result: 20"));
    REQUIRE(run_test("5 1 2 + 4 * + 3 -", "Result: 14"));
}

TEST_CASE("Errors.Errors") {
    REQUIRE(run_test("", "Error: No input provided"));
    REQUIRE(run_test("3 +", "Error: Too few operands"));
    REQUIRE(run_test("3 2 1 +", "Error: Invalid expression"));
    REQUIRE(run_test("4 0 /", "Error: Division by zero"));
    REQUIRE(run_test("xyz", "Error: Invalid token"));
}

TEST_CASE("Constants.Constants") {
    REQUIRE(run_test("pi", "Result: 3.14159"));
    REQUIRE(run_test("-pi", "Result: -3.14159"));
    REQUIRE(run_test("e", "Result: 2.71828"));
}
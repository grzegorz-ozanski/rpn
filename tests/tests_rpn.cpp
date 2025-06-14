#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "rpn.hpp"

namespace Rpn {
    bool run_test(const std::string& input, const std::string& output) {
        std::stringstream in(input + "\n");
        std::stringstream out;
        std::stringstream err;
        rpn::run(in, out, err);
        return (output.find("Error") != std::string::npos ? "" : rpn::prompt) + output + "\n" == (err.str().empty() ? out.str() : err.str());
    }

    TEST(Tests, ProsteOperacjeArytmetyczne) {
        EXPECT_TRUE(run_test("3 4 +", "Result: 7"));
        EXPECT_TRUE(run_test("10 2 /", "Result: 5"));
        EXPECT_TRUE(run_test("5 3 -", "Result: 2"));
        EXPECT_TRUE(run_test("6 7 *", "Result: 42"));
    }

    TEST(Tests, ZlozoneWyrazenia) {
        EXPECT_TRUE(run_test("2 3 + 4 *", "Result: 20"));
        EXPECT_TRUE(run_test("5 1 2 + 4 * + 3 -", "Result: 14"));
    }

    TEST(Tests, Bledy) {
        EXPECT_TRUE(run_test("", "Error: No input provided"));
        EXPECT_TRUE(run_test("3 +", "Error: Too few operands"));
        EXPECT_TRUE(run_test("3 2 1 +", "Error: Invalid expression"));
        EXPECT_TRUE(run_test("4 0 /", "Error: Division by zero"));
        EXPECT_TRUE(run_test("xyz", "Error: Invalid token"));
    }

    TEST(Tests, StaleMatematyczne) {
        EXPECT_TRUE(run_test("pi", "Result: 3.14159"));
        EXPECT_TRUE(run_test("-pi", "Result: -3.14159"));
        EXPECT_TRUE(run_test("e", "Result: 2.71828"));
    }
}
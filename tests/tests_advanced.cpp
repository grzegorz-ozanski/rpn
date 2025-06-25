#include "tests.hpp"

TEST_CASE("Tests.Advanced.AdvancedArithmetic") {
    REQUIRE(run_test("4 2 ^", "Result: 16"));
    REQUIRE(run_test("4 0.5 ^", "Result: 2"));
    REQUIRE(run_test("6 3 **", "Result: 216"));
    REQUIRE(run_test("11 abs", "Result: 11"));
    REQUIRE(run_test("-11 abs", "Result: 11"));
    REQUIRE(run_test("100 log", "Result: 2"));
    REQUIRE(run_test("e ln", "Result: 1"));
    REQUIRE(run_test("16 4 logn", "Result: 2"));
    REQUIRE(run_test("1e2", "Result: 100"));
}

TEST_CASE("Tests.Advanced.InvalidNumberOfOperands") {
    REQUIRE(run_test("2 -2 ^", "Result: 0.25"));
    REQUIRE(run_test("-2 -2 ^", "Result: 0.25"));
    REQUIRE(run_test("4 -0.5 ^", "Result: 0.5"));
    REQUIRE(run_test("-6 3 **", "Result: -216"));
    REQUIRE(run_test("-4 -0.5 ^", "Error: Negative base with non-integer exponent"));
    REQUIRE(run_test("0 0 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("1 0 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("1 1 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("10 1 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("0 1 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("-16 4 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("16 -4 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("-16 -4 logn", "Error: Logarithm domain error"));
    REQUIRE(run_test("1 0.5 logn", "Result: -0"));
}

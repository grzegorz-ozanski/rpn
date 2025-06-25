#include "tests.hpp"

TEST_CASE("Tests.Unknown.Operator") {
	using namespace rpn;
    
    try {
        Operator op(Token("reset"));
        FAIL("Expected exception not thrown");
    }
    catch (const std::runtime_error& ex) {
        REQUIRE(std::string(ex.what()) == "Unknown operator: reset");
    }
}

TEST_CASE("Tests.Unknown.Command") {
    using namespace rpn;

    try {
        Command op(Token("reset"));
        FAIL("Expected exception not thrown");
    }
    catch (const std::runtime_error& ex) {
        REQUIRE(std::string(ex.what()) == "Unknown command: reset");
    }
}

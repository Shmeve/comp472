#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test1") {
    int a = 1;
    int b = 2;
    REQUIRE(a != b);
}

TEST_CASE("Test2") {
    int a = 1;
    int b = 2;
    REQUIRE(a == b);
}

//
// Created by chris on 17.10.24.
//

// Catch2 includes
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include "TestTypes.hpp"

// A simple function to test
int divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return numerator / denominator;
}

SCENARIO("Dividing numbers", "[division]") {

    GIVEN("A numerator and a non-zero denominator") {
        int numerator = 10;
        int denominator = 2;

        WHEN("they are divided") {
            int result = divide(numerator, denominator);

            THEN("the result is the integer division of the two") {
                REQUIRE(result == 5);
            }
        }
    }

    GIVEN("A numerator and a denominator of zero") {
        int numerator = 10;
        int denominator = 0;

        WHEN("division is attempted") {
            THEN("it throws an invalid_argument exception") {
                REQUIRE_THROWS_AS(divide(numerator, denominator), std::invalid_argument);
            }
        }
    }

    GIVEN("Two negative numbers") {
        int numerator = -10;
        int denominator = -2;

        WHEN("they are divided") {
            int result = divide(numerator, denominator);

            THEN("the result is positive") {
                REQUIRE(result == 5);
            }
        }
    }
}

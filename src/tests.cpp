#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "mastermind.h"

TEST_CASE("EvaluateGuess with no overlap at all", "[EvaluateGuess]") {
    const auto secret = Code(red, green, blue, yellow);
    const auto guess = Code(black, black, white, white);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 0);
    REQUIRE(score.whites() == 0);
}

TEST_CASE("EvaluateGuess with exact match", "[EvaluateGuess]") {
    const auto secret = Code(red, green, blue, yellow);
    const auto guess = Code(red, green, blue, yellow);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 4);
    REQUIRE(score.whites() == 0);
}

TEST_CASE("EvaluateGuess with all correct colours but all wrong positions", "[EvaluateGuess]") {
    const auto secret = Code(red, green, blue, yellow);
    const auto guess = Code(yellow, blue, green, red);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 0);
    REQUIRE(score.whites() == 4);
}

TEST_CASE("EvaluateGuess with specific scenario 1", "[EvaluateGuess]") {
    const auto secret = Code(green, green, blue, blue);
    const auto guess = Code(blue, blue, green, green);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 0);
    REQUIRE(score.whites() == 4);
}

TEST_CASE("EvaluateGuess with specific scenario 2", "[EvaluateGuess]") {
    const auto secret = Code(green, green, blue, blue);
    const auto guess = Code(blue, blue, green, yellow);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 0);
    REQUIRE(score.whites() == 3);
}

TEST_CASE("EvaluateGuess with specific scenario 3", "[EvaluateGuess]") {
    const auto secret = Code(green, green, blue, yellow);
    const auto guess = Code(blue, blue, green, green);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 0);
    REQUIRE(score.whites() == 3);
}

TEST_CASE("EvaluateGuess with specific scenario 4", "[EvaluateGuess]") {
    const auto secret = Code(blue, yellow, white, white);
    const auto guess = Code(blue, white, yellow, yellow);
    const auto score = EvaluateGuess(secret, guess);
    REQUIRE(score.blacks() == 1);
    REQUIRE(score.whites() == 2);
}

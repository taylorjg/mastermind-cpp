#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "mastermind.h"

TEST_CASE("EvaluateGuess with no overlap at all", "[EvaluateGuess]") {
    const auto secret = Secret(red, green, blue, yellow);
    const auto guess = Guess(black, black, white, white);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 0);
    REQUIRE(feedback.whites() == 0);
}

TEST_CASE("EvaluateGuess with exact match", "[EvaluateGuess]") {
    const auto secret = Secret(red, green, blue, yellow);
    const auto guess = Guess(red, green, blue, yellow);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 4);
    REQUIRE(feedback.whites() == 0);
}

TEST_CASE("EvaluateGuess with all correct colours but all wrong positions", "[EvaluateGuess]") {
    const auto secret = Secret(red, green, blue, yellow);
    const auto guess = Guess(yellow, blue, green, red);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 0);
    REQUIRE(feedback.whites() == 4);
}

TEST_CASE("EvaluateGuess with specific scenario 1", "[EvaluateGuess]") {
    const auto secret = Secret(green, green, blue, blue);
    const auto guess = Guess(blue, blue, green, green);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 0);
    REQUIRE(feedback.whites() == 4);
}

TEST_CASE("EvaluateGuess with specific scenario 2", "[EvaluateGuess]") {
    const auto secret = Secret(green, green, blue, blue);
    const auto guess = Guess(blue, blue, green, yellow);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 0);
    REQUIRE(feedback.whites() == 3);
}

TEST_CASE("EvaluateGuess with specific scenario 3", "[EvaluateGuess]") {
    const auto secret = Secret(green, green, blue, yellow);
    const auto guess = Guess(blue, blue, green, green);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 0);
    REQUIRE(feedback.whites() == 3);
}

TEST_CASE("EvaluateGuess with specific scenario 4", "[EvaluateGuess]") {
    const auto secret = Secret(blue, yellow, white, white);
    const auto guess = Guess(blue, white, yellow, yellow);
    const auto feedback = EvaluateGuess(secret, guess);
    REQUIRE(feedback.blacks() == 1);
    REQUIRE(feedback.whites() == 2);
}

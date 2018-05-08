#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "mastermind.h"
#include "autosolve.h"

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

TEST_CASE("Autosolve with fixed secret solves within 5 guesses", "[Autosolve]") {
    const auto secret = Code(blue, yellow, white, white);
    std::vector<std::pair<Code, Score>> guesses;
    Autosolve([&secret, &guesses](const auto& guess){
        const auto score = EvaluateGuess(secret, guess);
        guesses.push_back(std::make_pair(guess, score));
        return score;
    });
    const auto numGuesses = guesses.size();
    REQUIRE((numGuesses >= 1 && numGuesses <= 5));
    const auto finalPair = guesses.back();
    const auto finalGuess = finalPair.first;
    const auto finalScore = finalPair.second;
    REQUIRE(finalGuess == secret);
    REQUIRE(finalScore.blacks() == 4);
    REQUIRE(finalScore.whites() == 0);
}

TEST_CASE("Autosolve with random secret solves within 5 guesses", "[Autosolve]") {
    const auto secret = GenerateSecret();
    std::vector<std::pair<Code, Score>> guesses;
    Autosolve([&secret, &guesses](const auto& guess){
        const auto score = EvaluateGuess(secret, guess);
        guesses.push_back(std::make_pair(guess, score));
        return score;
    });
    const auto numGuesses = guesses.size();
    REQUIRE((numGuesses >= 1 && numGuesses <= 5));
    const auto finalPair = guesses.back();
    const auto finalGuess = finalPair.first;
    const auto finalScore = finalPair.second;
    REQUIRE(finalGuess == secret);
    REQUIRE(finalScore.blacks() == 4);
    REQUIRE(finalScore.whites() == 0);
}

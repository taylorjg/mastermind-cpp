#include <vector>
#include <numeric>
#include <cstdlib>
#include "mastermind.h"

static Peg randomPeg() {
    const auto randomIndex = std::rand() % 6; // NOLINT
    return AllPegs()[randomIndex];
};

Code GenerateSecret() {
    return Code(
            randomPeg(),
            randomPeg(),
            randomPeg(),
            randomPeg());
};

static long CountMatchingPegs(const std::vector<Peg> &pegs, Peg p1) {
    return std::count_if(
            pegs.cbegin(),
            pegs.cend(),
            [p1](const auto p2) { return p1 == p2; });
};

Score EvaluateGuess(const Code &secret, const Code &guess) {
    const auto &secret_pegs = secret.pegs();
    const auto &guess_pegs = guess.pegs();
    const auto sum = std::accumulate(
            AllPegs().cbegin(),
            AllPegs().cend(),
            0,
            [&secret_pegs, &guess_pegs](const auto acc, const auto p) {
                const auto min = std::min(
                        CountMatchingPegs(secret_pegs, p),
                        CountMatchingPegs(guess_pegs, p));
                return acc + min;
            });
    const auto indices = {0, 1, 2, 3};
    const auto blacks = std::count_if(
            indices.begin(),
            indices.end(),
            [&secret_pegs, &guess_pegs](const auto index) {
                return secret_pegs[index] == guess_pegs[index];
            });
    const auto whites = sum - blacks;
    return Score(blacks, whites);
};

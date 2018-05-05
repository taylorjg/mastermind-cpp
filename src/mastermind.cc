#include "mastermind.h"

#include <vector>
#include <numeric>

Secret GenerateSecret() {
    return Secret(red, red, green, green);
};

long CountMatchingPegs(const std::vector<Peg> &pegs, Peg p) {
    return std::count_if(
            pegs.cbegin(),
            pegs.cend(),
            [p](Peg x) { return x == p; });
};

Feedback EvaluateGuess(const Secret &secret, const Guess &guess) {
    const auto &secret_pegs = secret.pegs();
    const auto &guess_pegs = guess.pegs();
    std::vector<int> mins(PEGS.size());
    std::transform(
            PEGS.cbegin(),
            PEGS.cend(),
            mins.begin(),
            [&secret_pegs, &guess_pegs](Peg p) {
                return std::min(
                        CountMatchingPegs(secret_pegs, p),
                        CountMatchingPegs(guess_pegs, p));
            });
    const auto sum = std::accumulate(mins.cbegin(), mins.cend(), 0);
    const auto blacks = std::count_if(
            secret_pegs.cbegin(),
            secret_pegs.cend(),
            [&secret_pegs, &guess_pegs](const Peg &p) {
                auto idx = &p - &secret_pegs[0];
                return p == guess_pegs[idx];
            });
    const auto whites = sum - blacks;
    return Feedback(blacks, whites);
};

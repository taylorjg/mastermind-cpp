#include <vector>
#include <numeric>
#include "mastermind.h"

Code GenerateSecret() {
    return Code(yellow, red, black, white);
};

static long CountMatchingPegs(const std::vector<Peg> &pegs, Peg peg) {
    return std::count_if(
            pegs.cbegin(),
            pegs.cend(),
            [&peg](const Peg &p) { return p == peg; });
};

Feedback EvaluateGuess(const Code &secret, const Code &guess) {
    const auto &secret_pegs = secret.pegs();
    const auto &guess_pegs = guess.pegs();
    std::vector<int> mins(AllPegs().size());
    std::transform(
            AllPegs().cbegin(),
            AllPegs().cend(),
            mins.begin(),
            [&secret_pegs, &guess_pegs](const Peg &p) {
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

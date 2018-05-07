#include <numeric>
#include <limits>
#include "autosolve.h"
#include "mastermind.h"

static const Code InitialGuess() {
    static const Code InitialGuess = Code(red, red, green, green);
    return InitialGuess;
};

static Code CalculateNewGuess(const std::set<Code> &set) {
    const auto best = std::reduce(
            AllCodes().cbegin(),
            AllCodes().cend(),
            std::make_pair(LONG_MAX, InitialGuess()),
            [&set](const std::pair<long, Code> &currentBest, const Code &unusedCode) {
                const auto max = std::reduce(
                        AllScores().cbegin(),
                        AllScores().cend(),
                        0L,
                        [&set, &unusedCode](const long currentMax, const Score &score) {
                            const auto thisMax = std::count_if(
                                    set.cbegin(),
                                    set.cend(),
                                    [&unusedCode, &score](const Code &code) {
                                        return EvaluateGuess(unusedCode, code) == score;
                                    });
                            return std::max(currentMax, thisMax);
                        });
                return (max < currentBest.first)
                       ? std::make_pair(max, unusedCode)
                       : currentBest;
            });
    return best.second;
};

std::tuple<const Code, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context) {
    if (context.empty()) {
        const auto initialGuess = InitialGuess();
        return {initialGuess, context};
    } else {
        const auto &lastGuess = context.lastGuess();
        const auto &lastCode = lastGuess.first;
        const auto &lastScore = lastGuess.second;

        std::set<Code> filteredSet;
        std::copy_if(
                context.set().cbegin(),
                context.set().cend(),
                std::inserter(filteredSet, filteredSet.end()),
                [&lastCode, &lastScore](const Code &code) {
                    return EvaluateGuess(code, lastCode) == lastScore;
                });

        const auto newContext = AutosolveContext(filteredSet, context.guesses());

        if (filteredSet.size() == 1) {
            const auto &newGuess = *filteredSet.cbegin();
            return {newGuess, newContext};
        }

        const auto newGuess = CalculateNewGuess(filteredSet);
        return {newGuess, newContext};
    }
}

const std::vector<std::pair<Code, Score>> Autosolve(
        const Code &secret,
        const AutosolveContext &context) {

    const auto&[guess, context2] = GenerateGuess(context);
    const auto score = EvaluateGuess(secret, guess);

    std::vector<std::pair<Code, Score>> guesses(context.guesses());
    guesses.emplace_back(guess, score);

    if (score.blacks() == 4) {
        return guesses;
    }

    const auto context3 = AutosolveContext(context2.set(), guesses);
    return Autosolve(secret, context3);
};

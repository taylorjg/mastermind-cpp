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

static void Autosolve(
        const std::set<Code> &set,
        const std::function<const Score(const Code &)> &attempt) {

    const auto guess = (set.size() == AllCodes().size()) ? InitialGuess() :
                       (set.size() == 1) ? *set.cbegin() : CalculateNewGuess(set);

    const auto score = attempt(guess);

    if (score.blacks() == 4) {
        return;
    }

    std::set<Code> filteredSet;
    std::copy_if(
            set.cbegin(),
            set.cend(),
            std::inserter(filteredSet, filteredSet.end()),
            [&guess, &score](const Code &code) {
                return EvaluateGuess(code, guess) == score;
            });

    Autosolve(filteredSet, attempt);
}

void Autosolve(const std::function<const Score(const Code &)> &attempt) {
    Autosolve(AllCodes(), attempt);
};

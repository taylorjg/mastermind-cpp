#include <numeric>
#include <limits>
#include "autosolve.h"
#include "mastermind.h"

static const Code InitialGuess() {
    static const Code InitialGuess = Code(red, red, green, green);
    return InitialGuess;
};

static bool EvaluatesToSameFeedback(
        const Code &code1,
        const Code &code2,
        const Feedback &feedback) {
    return EvaluateGuess(code1, code2) == feedback;
};

static Code CalculateNewGuess(
        const std::set<Code> &filteredSet,
        const std::set<Code> &unused) {
    const auto seed = std::make_pair(LONG_MAX, InitialGuess());
    const auto best = std::reduce(
            unused.cbegin(),
            unused.cend(),
            seed,
            [&filteredSet](const std::pair<long, Code> &currentBest, const Code &unusedCode) {
                const long max = std::reduce(
                        AllOutcomes().cbegin(),
                        AllOutcomes().cend(),
                        0L,
                        [&filteredSet, &unusedCode](const long currentMax, const Feedback &outcome) {
                            const auto count = std::count_if(
                                    filteredSet.cbegin(),
                                    filteredSet.cend(),
                                    [&unusedCode, &outcome](const Code &code) {
                                        return EvaluatesToSameFeedback(unusedCode, code, outcome);
                                    });
                            return std::max(currentMax, count);
                        });
                return (max < currentBest.first) ? std::make_pair(max, unusedCode) : currentBest;
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
        const auto &lastFeedback = lastGuess.second;

        std::set<Code> filteredSet;
        std::copy_if(
                context.set().cbegin(),
                context.set().cend(),
                std::inserter(filteredSet, filteredSet.end()),
                [&lastCode, &lastFeedback](const Code &code) {
                    return EvaluatesToSameFeedback(code, lastCode, lastFeedback);
                });

        const auto newContext = AutosolveContext(filteredSet, context.guesses());

        if (filteredSet.size() == 1) {
            const auto &newGuess = *filteredSet.cbegin();
            return {newGuess, newContext};
        }

        std::set<Code> used = context.used();
        std::set<Code> unused;
        std::copy_if(
                AllCodes().cbegin(),
                AllCodes().cend(),
                std::inserter(unused, unused.end()),
                [&lastCode, &used](const Code &code) {
                    return used.find(code) == used.cend();
                });

        const auto newGuess = CalculateNewGuess(filteredSet, unused);
        return {newGuess, newContext};
    }
}

const std::vector<std::pair<Code, Feedback>> Autosolve(
        const Code &secret,
        const AutosolveContext &context) {

    const auto&[guess, context2] = GenerateGuess(context);
    const auto feedback = EvaluateGuess(secret, guess);

    std::vector<std::pair<Code, Feedback>> guesses(context2.guesses());
    guesses.emplace_back(guess, feedback);

    if (feedback.blacks() == 4) {
        return guesses;
    }

    if (guesses.size() == 10) {
        return guesses;
    }

    const auto context3 = AutosolveContext(context2.set(), guesses);
    return Autosolve(secret, context3);
};

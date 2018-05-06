#include "autosolve.h"
#include "mastermind.h"

std::tuple<const Code, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context) {
    if (context.empty()) {
        const auto guess = Code(red, red, green, green);
        return {guess, context};
    } else {
        const auto&[lastCode, lastFeedback] = context.lastGuess();
        const auto guess = Code(red, red, green, green);
        return {guess, context};
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

#include "autosolve.h"

std::tuple<const Guess, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context) {
    if (context.empty()) {
        const auto guess = Guess(red, red, green, green);
        return {guess, context};
    } else {
        const auto guess = Guess(red, red, green, green);
        return {guess, context};
    }
}

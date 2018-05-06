#include "autosolve.h"

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

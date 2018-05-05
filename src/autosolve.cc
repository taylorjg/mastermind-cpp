#include "autosolve.h"

std::tuple<const Guess, const AutosolveContext> GenerateGuess(
    const AutosolveContext &context,
    const Guess &lastGuess,
    const Feedback &lastFeedback)
{
    auto used2 = std::set<Guess>(context.used());
    used2.insert(lastGuess);
    const auto context2 = AutosolveContext(context.set(), used2);
    return {lastGuess, context2};
}

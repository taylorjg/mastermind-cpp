#pragma once

#include <set>
#include <vector>
#include <tuple>
#include <utility>
#include "guess.h"
#include "feedback.h"

class AutosolveContext {
public:
    AutosolveContext()
            : m_set(ALL_GUESSES) {
    }

    AutosolveContext(
            std::set<Guess> set,
            std::vector<std::pair<Guess, Feedback>> guesses
    )
            : m_set(std::move(set)),
              m_guesses(std::move(guesses)) {
    }

    const std::set<Guess> &set() const {
        return m_set;
    }

    bool empty() const {
        return m_guesses.empty();
    }

    const std::tuple<const Guess, const Feedback> last() const {
        const auto lastPair = m_guesses.back();
        return {lastPair.first, lastPair.second};
    }

private:
    std::set<Guess> m_set;
    std::vector<std::pair<Guess, Feedback>> m_guesses;
};

extern std::tuple<const Guess, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context);

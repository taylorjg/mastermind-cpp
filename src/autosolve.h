#pragma once

#include <set>
#include <vector>
#include <tuple>
#include <utility>
#include "code.h"
#include "feedback.h"

class AutosolveContext {
public:
    AutosolveContext()
            : m_set(AllCodes()) {
    }

    AutosolveContext(
            std::set<Code> set,
            std::vector<std::pair<Code, Feedback>> codes
    )
            : m_set(std::move(set)),
              m_guesses(std::move(codes)) {
    }

    const std::set<Code> &set() const {
        return m_set;
    }

    const std::vector<std::pair<Code, Feedback>> &guesses() const {
        return m_guesses;
    }

    bool empty() const {
        return m_guesses.empty();
    }

    const std::tuple<const Code, const Feedback> lastGuess() const {
        return {m_guesses.back().first, m_guesses.back().second};
    }

private:
    std::set<Code> m_set;
    std::vector<std::pair<Code, Feedback>> m_guesses;
};

extern std::tuple<const Code, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context);

extern const std::vector<std::pair<Code, Feedback>> Autosolve(
        const Code &secret,
        const AutosolveContext &context);

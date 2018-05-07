#pragma once

#include <set>
#include <vector>
#include <tuple>
#include <utility>
#include "code.h"
#include "score.h"

class AutosolveContext {
public:
    AutosolveContext()
            : m_set(AllCodes()) {
    }

    AutosolveContext(
            std::set<Code> set,
            std::vector<std::pair<Code, Score>> guesses
    )
            : m_set(std::move(set)),
              m_guesses(std::move(guesses)) {
    }

    const std::set<Code> &set() const {
        return m_set;
    }

    const std::vector<std::pair<Code, Score>> &guesses() const {
        return m_guesses;
    }

    bool empty() const {
        return m_guesses.empty();
    }

    const std::pair<const Code, const Score> lastGuess() const {
        return m_guesses.back();
    }

    const std::set<Code> used() const {
        std::set<Code> result;
        std::transform(
                m_guesses.cbegin(),
                m_guesses.cend(),
                std::inserter(result, result.end()),
                [](const auto &pair) {
                    return pair.first;
                });
        return result;
    }

private:
    std::set<Code> m_set;
    std::vector<std::pair<Code, Score>> m_guesses;
};

extern std::tuple<const Code, const AutosolveContext> GenerateGuess(
        const AutosolveContext &context);

extern const std::vector<std::pair<Code, Score>> Autosolve(
        const Code &secret,
        const AutosolveContext &context);

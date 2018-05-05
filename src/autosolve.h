#pragma once

#include <set>
#include <tuple>
#include <utility>
#include "guess.h"
#include "feedback.h"

class AutosolveContext
{
  public:
    AutosolveContext()
        : m_set(ALL_GUESSES)
    {
    }
    AutosolveContext(std::set<Guess> set, std::set<Guess> used)
        : m_set(std::move(set)), m_used(std::move(used))
    {
    }

    const std::set<Guess> &set() const
    {
        return m_set;
    }
    const std::set<Guess> &used() const
    {
        return m_used;
    }

  private:
    std::set<Guess> m_set;
    std::set<Guess> m_used;
};

extern std::tuple<const Guess, const AutosolveContext> GenerateGuess(
    const AutosolveContext &context,
    const Guess &lastGuess,
    const Feedback &lastFeedback);

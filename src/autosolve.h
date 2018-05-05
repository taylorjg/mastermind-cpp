#pragma once

#include <set>

#include "guess.h"
#include "feedback.h"

class AutosolveContext
{
public:
  AutosolveContext()
      : m_set(ALL_GUESSES)
  {
  }
  AutosolveContext(const std::set<Guess> &set, const std::set<Guess> &used)
      : m_set(set), m_used(used)
  {
  }

private:
  std::set<Guess> m_set;
  std::set<Guess> m_used;
};

// class Autosolve
// {
// public:
//   Autosolve()
//   {
//   }

//   const Guess GenerateGuess(const Guess &lastGuess, const Feedback &lastFeedback);

// private:
//   // std::set<Guess> m_set;
//   // std::set<Guess> m_used;
// };

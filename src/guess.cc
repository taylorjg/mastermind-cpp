#include "guess.h"

const std::set<Guess> makeAllGuesses()
{
    std::set<Guess> allGuesses;
    for (auto p1 : PEGS)
        for (auto p2 : PEGS)
            for (auto p3 : PEGS)
                for (auto p4 : PEGS)
                    allGuesses.insert(Guess(p1, p2, p3, p4));
    return allGuesses;
}

const std::set<Guess> ALL_GUESSES = makeAllGuesses();

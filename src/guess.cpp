#include "guess.h"

static const std::set<Guess> makeAllGuesses() {
    std::set<Guess> allGuesses;
    for (auto p1 : AllPegs())
        for (auto p2 : AllPegs())
            for (auto p3 : AllPegs())
                for (auto p4 : AllPegs())
                    allGuesses.insert(Guess(p1, p2, p3, p4));
    return allGuesses;
}

const std::set<Guess> &AllGuesses() {
    static const std::set<Guess> AllGuesses = makeAllGuesses();
    return AllGuesses;
}

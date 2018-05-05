#pragma once

#include "code.h"

#include <set>

class Guess : public Code {
public:
    Guess(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
            : Code(peg0, peg1, peg2, peg3) {
    }
};

extern const std::set<Guess> ALL_GUESSES;

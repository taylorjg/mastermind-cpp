#include "peg.h"

#include <vector>

const std::vector<Peg> &AllPegs() {
    static std::vector<Peg> AllPegs{red, green, blue, yellow, black, white};
    return AllPegs;
}

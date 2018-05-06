#include <vector>
#include "peg.h"

const std::vector<Peg> &AllPegs() {
    static std::vector<Peg> AllPegs{red, green, blue, yellow, black, white};
    return AllPegs;
}

#include "code.h"

#include <algorithm>

extern bool operator==(const Code &a, const Code &b) {
    return std::equal(
            a.pegs().cbegin(),
            a.pegs().cend(),
            b.pegs().cbegin());
}

extern bool operator<(const Code &a, const Code &b) {
    return a.pegs() < b.pegs();
}

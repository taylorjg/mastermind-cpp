#include <algorithm>
#include "code.h"

extern bool operator==(const Code &a, const Code &b) {
    return std::equal(
            a.pegs().cbegin(),
            a.pegs().cend(),
            b.pegs().cbegin());
}

extern bool operator<(const Code &a, const Code &b) {
    return a.pegs() < b.pegs();
}

static const std::set<Code> makeAllCodes() {
    std::set<Code> allCodes;
    for (auto p1 : AllPegs())
        for (auto p2 : AllPegs())
            for (auto p3 : AllPegs())
                for (auto p4 : AllPegs())
                    allCodes.insert(Code(p1, p2, p3, p4));
    return allCodes;
}

const std::set<Code> &AllCodes() {
    static const std::set<Code> AllCodes = makeAllCodes();
    return AllCodes;
}

std::ostream &operator<<(std::ostream &outputStream, const Code &code) {
    const auto &pegs = code.pegs();
    outputStream << pegs[0] << pegs[1] << pegs[2] << pegs[3];
    return outputStream;
}

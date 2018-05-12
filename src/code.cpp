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

static const std::unordered_set<Code> MakeAllCodes() {
    std::unordered_set<Code> allCodes;
    for (const auto p1 : AllPegs())
        for (const auto p2 : AllPegs())
            for (const auto p3 : AllPegs())
                for (const auto p4 : AllPegs())
                    allCodes.insert(Code(p1, p2, p3, p4));
    return allCodes;
}

const std::unordered_set<Code> &AllCodes() {
    static const std::unordered_set<Code> allCodes = MakeAllCodes();
    return allCodes;
}

std::ostream &operator<<(std::ostream &outputStream, const Code &code) {
    const auto &pegs = code.pegs();
    outputStream << pegs[0] << pegs[1] << pegs[2] << pegs[3];
    return outputStream;
}

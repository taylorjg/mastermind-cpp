#pragma once

#include <vector>
#include <ostream>
#include <set>
#include "peg.h"

class Code {
public:
    Code(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
            : m_pegs{peg0, peg1, peg2, peg3} {
    }

    const std::vector<Peg> &pegs() const {
        return m_pegs;
    }

private:
    std::vector<Peg> m_pegs;
};

extern bool operator==(const Code &a, const Code &b);

extern bool operator<(const Code &a, const Code &b);

namespace std {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"

    template<>
    struct hash<Code> {
        size_t operator()(const Code &code) const {
            const auto &pegs = code.pegs();
            auto hasher = hash<int>();
            auto h0 = hasher(pegs[0]) * 8976553;
            auto h1 = hasher(pegs[1]) * 33456;
            auto h2 = hasher(pegs[2]) * 57246351;
            auto h3 = hasher(pegs[3]) * 1865874;
            return h0 ^ h1 ^ h2 ^ h3;
        }
    };

#pragma clang diagnostic pop
}

extern std::ostream &operator<<(std::ostream &outputStream, const Code &code);

extern const std::set<Code> &AllCodes();

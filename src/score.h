#pragma once

#include <unordered_set>
#include <ostream>

class Score {
public:
    Score(long blacks, long whites)
            : m_blacks(blacks),
              m_whites(whites) {
    }

    long blacks() const {
        return m_blacks;
    }

    long whites() const {
        return m_whites;
    }

private:
    long m_blacks;
    long m_whites;
};

extern bool operator==(const Score &a, const Score &b);

extern bool operator<(const Score &a, const Score &b);

namespace std {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedStructInspection"

    template<>
    struct hash<Score> {
        size_t operator()(const Score &score) const {
            auto hasher = hash<long>();
            auto h0 = hasher(score.blacks()) * 8976553;
            auto h1 = hasher(score.whites()) * 33456;
            return h0 ^ h1;
        }
    };

#pragma clang diagnostic pop
}

extern std::ostream &operator<<(std::ostream &outputStream, const Score &score);

extern const std::unordered_set<Score> &AllScores();

#pragma once

#include <set>

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

extern const std::set<Score> &AllScores();

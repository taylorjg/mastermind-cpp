#pragma once

#include <set>

class Feedback {
public:
    Feedback(long blacks, long whites)
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

extern bool operator==(const Feedback &a, const Feedback &b);

extern bool operator<(const Feedback &a, const Feedback &b);

extern const std::set<Feedback> &AllOutcomes();

#include "score.h"

extern bool operator==(const Score &a, const Score &b) {
    return a.blacks() == b.blacks() && a.whites() == b.whites();
};

extern bool operator<(const Score &a, const Score &b) {
    return a.blacks() < b.blacks() || a.whites() < b.whites();
};

static const std::set<Score> makeAllOutcomes() {
    std::set<Score> allOutcomes;
    for (auto blacks : {0, 1, 2, 3, 4})
        for (auto whites : {0, 1, 2, 3, 4}) {
            if (blacks + whites > 4)
                continue;
            if (blacks == 3 && whites == 1)
                continue;
            allOutcomes.insert(Score(blacks, whites));
        }
    return allOutcomes;
}

const std::set<Score> &AllScores() {
    static const std::set<Score> AllOutcomes = makeAllOutcomes();
    return AllOutcomes;
};

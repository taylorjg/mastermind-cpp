#include "feedback.h"

extern bool operator==(const Feedback &a, const Feedback &b) {
    return a.blacks() == b.blacks() && a.whites() == b.whites();
};

extern bool operator<(const Feedback &a, const Feedback &b) {
    return a.blacks() < b.blacks() || a.whites() < b.whites();
};

const std::set<Feedback> makeAllOutcomes() {
    std::set<Feedback> allOutcomes;
    for (auto blacks : {0, 1, 2, 3, 4})
        for (auto whites : {0, 1, 2, 3, 4}) {
            if (blacks + whites > 4)
                continue;
            if (blacks == 3 && whites == 1)
                continue;
            allOutcomes.insert(Feedback(blacks, whites));
        }
    return allOutcomes;
}

const std::set<Feedback> &AllOutcomes() {
    static const std::set<Feedback> AllOutcomes = makeAllOutcomes();
    return AllOutcomes;
};

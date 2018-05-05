#include "feedback.h"

const std::vector<Feedback> makeAllOutcomes()
{
    std::vector<Feedback> allOutcomes;
    for (auto blacks : {0, 1, 2, 3, 4})
        for (auto whites : {0, 1, 2, 3, 4})
        {
            if (blacks + whites > 4)
                continue;
            if (blacks == 3 && whites == 1)
                continue;
            allOutcomes.push_back(Feedback(blacks, whites));
        }
    return allOutcomes;
}

const std::vector<Feedback> ALL_OUTCOMES = makeAllOutcomes();

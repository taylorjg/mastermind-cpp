#include <numeric>
#include <iterator>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <iostream>
#include "autosolve.h"
#include "mastermind.h"

static const Code InitialGuess() {
    static const Code InitialGuess = Code(red, red, green, green);
    return InitialGuess;
};

typedef std::pair<
        std::unordered_set<Code>::const_iterator,
        std::unordered_set<Code>::const_iterator> Chunk;

static const std::vector<Chunk> MakeChunks() {
    std::vector<Chunk> chunks;
    const auto numChunks = 8;
    const auto allCodesSize = AllCodes().size();
    const auto chunkSize = allCodesSize / numChunks;
    auto chunkStartIter = AllCodes().cbegin();
    const auto lastChunkIndex = numChunks - 1;
    for (auto index = 0; index <= lastChunkIndex; ++index) {
        auto thisChunkSize = index == lastChunkIndex ? allCodesSize - index * chunkSize : chunkSize;
        auto chunkEndIter = chunkStartIter;
        std::advance(chunkEndIter, thisChunkSize);
        chunks.emplace_back(chunkStartIter, chunkEndIter);
        chunkStartIter = chunkEndIter;
    }
    return chunks;
};

static const std::vector<Chunk> &Chunks() {
    static const std::vector<Chunk> chunks = MakeChunks();
    return chunks;
};

static const std::pair<long, Code> SubTask(
        const std::unordered_set<Code> &set,
        const std::unordered_set<Code>::const_iterator &startIter,
        const std::unordered_set<Code>::const_iterator &endIter) {
    const auto best = std::reduce(
            startIter,
            endIter,
            std::make_pair(LONG_MAX, InitialGuess()),
            [&set](const std::pair<long, Code> &currentBest, const Code &unusedCode) {
                const auto max = std::reduce(
                        AllScores().cbegin(),
                        AllScores().cend(),
                        0L,
                        [&set, &unusedCode](const long currentMax, const Score &score) {
                            const auto thisMax = std::count_if(
                                    set.cbegin(),
                                    set.cend(),
                                    [&unusedCode, &score](const Code &code) {
                                        return EvaluateGuess(unusedCode, code) == score;
                                    });
                            return std::max(currentMax, thisMax);
                        });
                return (max < currentBest.first)
                       ? std::make_pair(max, unusedCode)
                       : currentBest;
            });
    return best;
};

static Code CalculateNewGuess(const std::unordered_set<Code> &set) {
    std::vector<std::pair<long, Code>> results;
    std::transform(
            Chunks().cbegin(),
            Chunks().cend(),
            std::back_inserter(results),
            [&set](const auto &chunk) {
                return SubTask(set, chunk.first, chunk.second);
            });
    auto bestIter = std::min_element(
            results.cbegin(),
            results.cend(),
            [](const auto &p1, const auto &p2) { return p1.first < p2.first; });
    return bestIter->second;
};

static void Autosolve(
        const std::unordered_set<Code> &set,
        const std::function<const Score(const Code &)> &attempt) {

    const auto guess = (set.size() == AllCodes().size()) ? InitialGuess() :
                       (set.size() == 1) ? *set.cbegin() : CalculateNewGuess(set);

    const auto score = attempt(guess);

    if (score.blacks() == 4) {
        return;
    }

    std::unordered_set<Code> filteredSet;
    std::copy_if(
            set.cbegin(),
            set.cend(),
            std::inserter(filteredSet, filteredSet.end()),
            [&guess, &score](const Code &code) {
                return EvaluateGuess(code, guess) == score;
            });

    Autosolve(filteredSet, attempt);
}

void Autosolve(const std::function<const Score(const Code &)> &attempt) {
    Autosolve(AllCodes(), attempt);
};

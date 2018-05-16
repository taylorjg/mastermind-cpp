#include <numeric>
#include <iterator>
#include <algorithm>
#include <vector>
#include <thread>
#include <future>
#include <limits>
#include "autosolve.h"
#include "mastermind.h"

static const Code InitialGuess() {
    static const Code InitialGuess = Code(red, red, green, green);
    return InitialGuess;
};

typedef std::pair<
        std::set<Code>::const_iterator,
        std::set<Code>::const_iterator> Chunk;

static const std::vector<Chunk> MakeChunks(const int numChunks) {
    std::vector<Chunk> chunks;
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

static const std::pair<long, Code> SubTask(
        const std::set<Code> &set,
        const std::set<Code>::const_iterator &startIter,
        const std::set<Code>::const_iterator &endIter) {
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

static Code CalculateNewGuessSeq(
        const AutosolveConfig &config,
        const std::set<Code> &set) {
    return SubTask(set, AllCodes().cbegin(), AllCodes().cend()).second;
};

static Code CalculateNewGuessPar(
        const AutosolveConfig &config,
        const std::set<Code> &set) {

    const auto &chunks = MakeChunks(config.numThreads);

    std::vector<std::future<const std::pair<long, Code>>> futures;
    std::transform(
            chunks.cbegin(),
            chunks.cend(),
            std::back_inserter(futures),
            [&set](const auto &chunk) -> std::future<const std::pair<long, Code>> {
                return std::async(SubTask, set, chunk.first, chunk.second);
            });

    std::vector<const std::pair<long, Code>> results;
    std::transform(
            futures.begin(),
            futures.end(),
            std::back_inserter(results),
            [](auto &f) { return f.get(); });

    auto bestIter = std::min_element(
            results.cbegin(),
            results.cend(),
            [](const auto &p1, const auto &p2) { return p1.first < p2.first; });

    return bestIter->second;
};

static Code CalculateNewGuess(
        const AutosolveConfig &config,
        const std::set<Code> &set) {
    if (config.enableParallelism && set.size() >= config.setSizeThreshold) {
        return CalculateNewGuessPar(config, set);
    } else {
        return CalculateNewGuessSeq(config, set);
    }
};

static std::set<Code> filterSet(
        const std::set<Code> &set,
        const Code &guess,
        const Score &score) {
    std::set<Code> filteredSet;
    std::copy_if(
            set.cbegin(),
            set.cend(),
            std::inserter(filteredSet, filteredSet.end()),
            [&guess, &score](const Code &code) {
                return EvaluateGuess(code, guess) == score;
            });
    return filteredSet;
};

static void Autosolve(
        const AutosolveConfig &config,
        const std::function<const Score(const Code &)> &attempt,
        const std::set<Code> &set) {

    const auto guess = (set.size() == AllCodes().size()) ? InitialGuess() :
                       (set.size() == 1) ? *set.cbegin() : CalculateNewGuess(config, set);

    const auto score = attempt(guess);

    if (score.blacks() == 4) {
        return;
    }

    Autosolve(config, attempt, filterSet(set, guess, score));
}

void Autosolve(
        const AutosolveConfig &config,
        const std::function<const Score(const Code &)> &attempt) {
    Autosolve(config, attempt, AllCodes());
};

#pragma once

#include "code.h"
#include "score.h"

struct AutosolveConfig {
    bool enableParallelism;
    int numThreads;
    int setSizeThreshold;

    AutosolveConfig(
            bool enableParallelism_,
            int numThreads_,
            int setSizeThreshold_
    )
            : enableParallelism(enableParallelism_),
              numThreads(numThreads_),
              setSizeThreshold(setSizeThreshold_) {}
};

extern void Autosolve(
        const AutosolveConfig &autosolveConfig,
        const std::function<const Score(const Code &)> &attempt);

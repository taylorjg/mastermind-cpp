#pragma once

#include "code.h"
#include "score.h"

extern void Autosolve(const std::function<const Score(const Code &)> &attempt);

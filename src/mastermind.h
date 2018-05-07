#pragma once

#include "code.h"
#include "score.h"

extern Code GenerateSecret();

extern Score EvaluateGuess(const Code &secret, const Code &guess);

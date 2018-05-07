#pragma once

#include "code.h"
#include "feedback.h"

extern Code GenerateSecret();

extern Feedback EvaluateGuess(const Code &secret, const Code &guess);

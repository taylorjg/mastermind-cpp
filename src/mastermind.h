#pragma once

#include <vector>

#include "secret.h"
#include "guess.h"
#include "feedback.h"

extern Secret GenerateSecret();

extern Feedback EvaluateGuess(const Secret &secret, const Guess &guess);

#pragma once

class Code;
class Score;

extern void Autosolve(const std::function<const Score(const Code &)> &attempt);

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "mastermind.h"
#include "autosolve.h"

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr)));

    const auto secret = GenerateSecret();
    std::vector<std::pair<Code, Score>> guesses;
    std::cout << "secret: " << secret << std::endl;
    Autosolve([&secret, &guesses](const auto &guess) {
        const auto score = EvaluateGuess(secret, guess);
        guesses.push_back(std::make_pair(guess, score));
        return score;
    });

    std::cout << "Number of guesses: " << guesses.size() << std::endl;

    std::for_each(
            guesses.cbegin(),
            guesses.cend(),
            [](const auto &pair) {
                const auto &code = pair.first;
                const auto &score = pair.second;
                std::cout << "guess: " << code << " " << "score: " << score << std::endl;
            });
}

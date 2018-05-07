#include <iostream>
#include <sstream>
#include <algorithm>
#include "mastermind.h"
#include "autosolve.h"

int main() {
    const auto secret = GenerateSecret();
    std::vector<std::pair<Code, Score>> guesses;
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
                const auto code = pair.first;
                const auto score = pair.second;
                std::stringstream sscode;
                std::stringstream ssscore;
                sscode << code.pegs()[0] << code.pegs()[1] << code.pegs()[2] << code.pegs()[3];
                ssscore << score.blacks() << score.whites();
                std::cout
                        << "guess: " << sscode.str()
                        << " "
                        << "score: " << ssscore.str()
                        << std::endl;
            });
}

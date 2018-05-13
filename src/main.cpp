#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "mastermind.h"
#include "autosolve.h"

static void AutosolveAllCodes() {
    auto hist = std::map<int, int>();
    for (const auto &secret : AllCodes()) {
        std::vector<std::pair<Code, Score>> guesses;
        Autosolve([&secret, &guesses](const auto &guess) {
            const auto score = EvaluateGuess(secret, guess);
            guesses.push_back(std::make_pair(guess, score));
            return score;
        });
        const auto numGuesses = guesses.size();
        std::cout << "secret: " << secret << " => #guesses: " << numGuesses << std::endl;
        ++hist[numGuesses];
    }
    for (const auto p : hist) {
        std::cout
                << std::fixed << std::setprecision(1) << std::setw(1) << p.first
                << " "
                << std::fixed << std::setprecision(1) << std::setw(4) << p.second
                << " "
                << std::string(static_cast<unsigned>(p.second / 12), '*')
                << std::endl;
    }
}

static void AutosolveRandomCode() {
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

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-all") == 0) {
        AutosolveAllCodes();
    } else {
        AutosolveRandomCode();
    }
}

#include <iostream>
#include <sstream>
#include <algorithm>
#include "mastermind.h"
#include "autosolve.h"

int main() {
    auto secret = GenerateSecret();
    auto initialContext = AutosolveContext();
    const auto guesses = Autosolve(secret, initialContext);
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

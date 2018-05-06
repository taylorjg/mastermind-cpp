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
            guesses.cend(), [](const std::pair<Code, Feedback> &pair) {
                const auto code = pair.first;
                const auto feedback = pair.second;
                std::stringstream sscode;
                std::stringstream ssfeedback;
                sscode << code.pegs()[0] << code.pegs()[1] << code.pegs()[2] << code.pegs()[3];
                ssfeedback << feedback.blacks() << feedback.whites();
                std::cout
                        << "guess: " << sscode.str()
                        << " "
                        << "feedback: " << ssfeedback.str()
                        << std::endl;
            });
}

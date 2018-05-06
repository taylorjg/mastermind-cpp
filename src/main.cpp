#include "mastermind.h"
#include "autosolve.h"

#include <iostream>

int main() {

    std::cout << "AllCodes().size(): " << AllCodes().size() << std::endl;
    std::cout << "AllOutcomes().size(): " << AllOutcomes().size() << std::endl;

    auto secret = GenerateSecret();
    auto guess = Code(red, green, red, blue);
    auto feedback = EvaluateGuess(secret, guess);
    std::cout
            << "blacks: " << feedback.blacks()
            << "; whites: " << feedback.whites()
            << std::endl;

    auto initialContext = AutosolveContext();
    const auto guesses = Autosolve(secret, initialContext);
    std::cout << "guesses.size(): " << guesses.size() << std::endl;
}

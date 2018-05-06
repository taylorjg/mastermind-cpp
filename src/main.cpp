#include "mastermind.h"
#include "autosolve.h"

#include <iostream>

int main() {
    auto secret = GenerateSecret();
    auto initialContext = AutosolveContext();
    const auto guesses = Autosolve(secret, initialContext);
    std::cout << "Number of guesses: " << guesses.size() << std::endl;
}

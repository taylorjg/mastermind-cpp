#include "mastermind.h"
#include "autosolve.h"

#include <iostream>

int main() {
    auto secret = GenerateSecret();
    auto guess = Guess(red, green, red, blue);
    auto feedback = EvaluateGuess(secret, guess);
    std::cout
            << "blacks: " << feedback.blacks()
            << "; whites: " << feedback.whites()
            << std::endl;

    auto guess1 = Guess(red, red, blue, blue);
    auto guess2 = Guess(red, red, blue, blue);
    auto guess3 = Guess(red, red, green, green);

    std::cout << "guess1 == guess2: " << (guess1 == guess2) << std::endl;
    std::cout << "guess1 == guess3: " << (guess1 == guess3) << std::endl;

    std::set<Guess> s{guess1, guess1, guess2, guess2, guess3, guess3};
    std::cout << "s.size(): " << s.size() << std::endl;

    std::cout << "ALL_GUESSES.size(): " << ALL_GUESSES.size() << std::endl;
    std::cout << "ALL_OUTCOMES.size(): " << ALL_OUTCOMES.size() << std::endl;

    auto context = AutosolveContext();
    const auto&[t0, t1] = GenerateGuess(context);
    std::cout << "t0.pegs[0]: " << t0.pegs()[0] << std::endl;
    std::cout << "t0.pegs[1]: " << t0.pegs()[1] << std::endl;
    std::cout << "t0.pegs[2]: " << t0.pegs()[2] << std::endl;
    std::cout << "t0.pegs[3]: " << t0.pegs()[3] << std::endl;
}

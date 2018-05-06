#include "mastermind.h"
#include "autosolve.h"

#include <iostream>

int main() {
    auto secret = GenerateSecret();
    auto guess = Code(red, green, red, blue);
    auto feedback = EvaluateGuess(secret, guess);
    std::cout
            << "blacks: " << feedback.blacks()
            << "; whites: " << feedback.whites()
            << std::endl;

    auto guess1 = Code(red, red, blue, blue);
    auto guess2 = Code(red, red, blue, blue);
    auto guess3 = Code(red, red, green, green);

    std::cout << "guess1 == guess2: " << (guess1 == guess2) << std::endl;
    std::cout << "guess1 == guess3: " << (guess1 == guess3) << std::endl;

    std::set<Code> s{guess1, guess1, guess2, guess2, guess3, guess3};
    std::cout << "s.size(): " << s.size() << std::endl;

    std::cout << "AllCodes().size(): " << AllCodes().size() << std::endl;
    std::cout << "AllOutcomes().size(): " << AllOutcomes().size() << std::endl;

    auto context = AutosolveContext();
    const auto&[t0, t1] = GenerateGuess(context);
    std::cout << "t0.pegs[0]: " << t0.pegs()[0] << std::endl;
    std::cout << "t0.pegs[1]: " << t0.pegs()[1] << std::endl;
    std::cout << "t0.pegs[2]: " << t0.pegs()[2] << std::endl;
    std::cout << "t0.pegs[3]: " << t0.pegs()[3] << std::endl;
}

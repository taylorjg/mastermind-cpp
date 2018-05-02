#include "mastermind.h"

#include <iostream>

int main()
{
    auto secret = GenerateSecret();
    auto guess = Guess(red, green, red, blue);
    auto feedback = EvaluateGuess(secret, guess);
    
    std::cout
        << "blacks: " << feedback.blacks()
        << "; whites: " << feedback.whites()
        << std::endl;
}

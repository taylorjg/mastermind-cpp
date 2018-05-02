#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

enum Peg
{
    red,
    green,
    blue,
    yellow,
    black,
    white
};

const std::vector<Peg> PEGS{red, green, blue, yellow, black, white};

class Code
{
  public:
    Code(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
        : m_pegs{peg0, peg1, peg2, peg3}
    {
    }

    const std::vector<Peg> &pegs() const
    {
        return m_pegs;
    }

  private:
    std::vector<Peg> m_pegs;
};

class Guess : public Code
{
  public:
    Guess(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
        : Code(peg0, peg1, peg2, peg3)
    {
    }
};

class Secret : public Code
{
  public:
    Secret(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
        : Code(peg0, peg1, peg2, peg3)
    {
    }
};

class Feedback
{
  public:
    Feedback(int blacks, int whites)
        : m_blacks(blacks),
          m_whites(whites)
    {
    }

    int blacks() const
    {
        return m_blacks;
    }

    int whites() const
    {
        return m_whites;
    }

  private:
    int m_blacks;
    int m_whites;
};

Secret GenerateSecret()
{
    return Secret(red, red, green, green);
};

int CountMatchingPegs(const std::vector<Peg> &pegs, Peg p)
{
    return std::count_if(
        pegs.cbegin(),
        pegs.cend(),
        [p](Peg x) { return x == p; });
};

Feedback EvaluateGuess(const Secret &secret, const Guess &guess)
{
    const auto secret_pegs = secret.pegs();
    const auto guess_pegs = guess.pegs();
    std::vector<int> mins(PEGS.size());
    std::transform(
        PEGS.cbegin(),
        PEGS.cend(),
        mins.begin(),
        [&secret_pegs, &guess_pegs](Peg p) {
            return std::min(
                CountMatchingPegs(secret_pegs, p),
                CountMatchingPegs(guess_pegs, p));
        });
    const auto sum = std::accumulate(mins.cbegin(), mins.cend(), 0);
    const auto blacks = std::count_if(
        secret_pegs.cbegin(),
        secret_pegs.cend(),
        [&secret_pegs, &guess_pegs](const Peg &p) {
            auto idx = &p - &secret_pegs[0];
            return p == guess_pegs[idx];
        });
    const auto whites = sum - blacks;
    return Feedback(blacks, whites);
};

int main()
{
    auto secret = GenerateSecret();
    auto guess = Guess(red, green, red, blue);
    auto feedback = EvaluateGuess(secret, guess);
    std::cout << "blacks: " << feedback.blacks() << "; whites: " << feedback.whites() << std::endl;
}

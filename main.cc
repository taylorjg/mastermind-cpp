#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

enum peg
{
    red,
    green,
    blue,
    yellow,
    black,
    white
};

const std::vector<peg> PEGS{red, green, blue, yellow, black, white};

class code_t
{
  public:
    code_t(peg peg0, peg peg1, peg peg2, peg peg3)
        : m_pegs{peg0, peg1, peg2, peg3}
    {
    }

    const std::vector<peg> &pegs() const
    {
        return m_pegs;
    }

  private:
    std::vector<peg> m_pegs;
};

class guess_t : public code_t
{
  public:
    guess_t(peg peg0, peg peg1, peg peg2, peg peg3)
        : code_t(peg0, peg1, peg2, peg3)
    {
    }
};

class secret_t : public code_t
{
  public:
    secret_t(peg peg0, peg peg1, peg peg2, peg peg3)
        : code_t(peg0, peg1, peg2, peg3)
    {
    }
};

class feedback_t
{
  public:
    feedback_t(int blacks, int whites)
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

secret_t generateSecret()
{
    return secret_t(red, red, green, green);
};

int count_matching_pegs(const std::vector<peg> &pegs, peg p)
{
    return std::count_if(
        pegs.cbegin(),
        pegs.cend(),
        [p](peg x) { return x == p; });
};

feedback_t evaluateGuess(const secret_t &secret, const guess_t &guess)
{
    const auto secret_pegs = secret.pegs();
    const auto guess_pegs = guess.pegs();
    std::vector<int> mins(PEGS.size());
    std::transform(
        PEGS.cbegin(),
        PEGS.cend(),
        mins.begin(),
        [&secret_pegs, &guess_pegs](peg p) {
            return std::min(
                count_matching_pegs(secret_pegs, p),
                count_matching_pegs(guess_pegs, p));
        });
    const auto sum = std::accumulate(mins.cbegin(), mins.cend(), 0);
    const auto blacks = std::count_if(
        secret_pegs.cbegin(),
        secret_pegs.cend(),
        [&secret_pegs, &guess_pegs](const peg &p) {
            auto idx = &p - &secret_pegs[0];
            return p == guess_pegs[idx];
        });
    const auto whites = sum - blacks;
    return feedback_t(blacks, whites);
};

int main()
{
    auto secret = generateSecret();
    auto guess = guess_t(red, green, red, blue);
    auto feedback = evaluateGuess(secret, guess);
    std::cout << "blacks: " << feedback.blacks() << "; whites: " << feedback.whites() << std::endl;
}

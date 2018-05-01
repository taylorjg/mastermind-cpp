#include <iostream>

enum peg
{
    red,
    green,
    blue,
    yellow,
    black,
    white
};

class code_t
{
  public:
    code_t(peg peg0, peg peg1, peg peg2, peg peg3)
        : m_pegs{peg0, peg1, peg2, peg3}
    {
    }

  private:
    peg m_pegs[4];
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
        : m_blacks(black),
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

feedback_t evaluateGuess(const secret_t &secret, const guess_t &guess)
{
    return feedback_t(4, 0);
};

int main()
{
    std::cout << "Hello" << std::endl;
}

#pragma once

#include <vector>

#include "peg.h"

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

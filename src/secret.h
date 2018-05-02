#pragma once

#include "code.h"

class Secret : public Code
{
  public:
    Secret(Peg peg0, Peg peg1, Peg peg2, Peg peg3)
        : Code(peg0, peg1, peg2, peg3)
    {
    }
};

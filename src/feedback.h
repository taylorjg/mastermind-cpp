#pragma once

#include <vector>

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

extern const std::vector<Feedback> ALL_OUTCOMES;

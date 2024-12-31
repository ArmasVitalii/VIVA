#include "Cascade.h"

Cascade::Cascade()
{
    m_description = "Cascade: Choose a row with at least 3 occupied positions. The stacks on that row move towards an edge, forming a new stack.";
}

void Cascade::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Cascade::usePower() const
{
    std::cout << "Cascade power activated: Move stacks on a chosen row towards an edge, forming a new stack." << std::endl;
}

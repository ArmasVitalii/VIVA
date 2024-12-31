#include "Tide.h"

Tide::Tide()
{
    m_description = "Tide: Swaps the positions of two stacks of cards.";
}

void Tide::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Tide::usePower() const
{
    std::cout << "Tide power activated: Swaps the positions of two stacks of cards." << std::endl;
}

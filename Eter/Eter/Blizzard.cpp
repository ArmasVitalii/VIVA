#include "Blizzard.h"

Blizzard::Blizzard()
{
    m_description = "Blizzard: Returns a visible opponent's card to their hand.";
}

void Blizzard::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Blizzard::usePower() const
{
    std::cout << "Blizzard power activated: Returns a visible opponent's card to their hand." << std::endl;
}

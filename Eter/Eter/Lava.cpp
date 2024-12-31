#include "Lava.h"

Lava::Lava()
{
    m_description = "Lava: Choose a number with at least 2 cards of that number visible on the board. All visible cards with that number return to their owners' hands.";
}

void Lava::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Lava::usePower() const
{
    std::cout << "Lava power activated: All visible cards of the chosen number return to their owners' hands." << std::endl;
}

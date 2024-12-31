#include "Earthquake.h"

Earthquake::Earthquake()
{
    m_description = "Earthquake: Removes all visible cards with the number 1 from the board.";
}

void Earthquake::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Earthquake::usePower() const
{
    std::cout << "Earthquake power activated: Removes all visible cards with the number 1 from the board." << std::endl;
}

#include "Crack.h"

Crack::Crack()
{
    m_description = "Crack: Decrease the value of an opponent's card (2/3/4) by 1.";
}

void Crack::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Crack::usePower() const
{
    std::cout << "Crack power activated: Decrease the value of an opponent's card by 1." << std::endl;
}

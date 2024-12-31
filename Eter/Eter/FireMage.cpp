#include "FireMage.h"

FireMage::FireMage()
{
    m_description = "FireMage: Removes a row of cards from the board containing at least 3 positions and one own card.";
}

void FireMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void FireMage::usePower() const
{
    std::cout << "FireMage uses power to remove a row of cards!" << std::endl;
}

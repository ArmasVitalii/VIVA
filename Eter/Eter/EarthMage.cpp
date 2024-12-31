#include "EarthMage.h"

EarthMage::EarthMage()
{
    m_description = "EarthMage: Removes an opponent's card from the board that is covering one's own card.";
}

void EarthMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void EarthMage::usePower() const
{
    std::cout << "EarthMage uses power to remove an opponent's card!" << std::endl;
}

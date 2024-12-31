#include "LightMage.h"

LightMage::LightMage()
{
    m_description = "LightMage: Gains an extra Eter card that is immediately placed on the board.";
}

void LightMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void LightMage::usePower() const
{
    std::cout << "LightMage uses power to gain an extra Ether card!" << std::endl;
}
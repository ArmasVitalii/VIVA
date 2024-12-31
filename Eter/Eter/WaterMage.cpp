#include "WaterMage.h"

WaterMage::WaterMage()
{
    m_description = "WaterMage: Covers an opponent's card with one's own card of a strictly lower value from hand.";
}

void WaterMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void WaterMage::usePower() const
{
    std::cout << "WaterMage uses power to cover an opponent's card!" << std::endl;
}
